// tcpclient.cpp
#include "tcpclient.h"
#include <QDebug>
#include <QThread>
#include <QHostAddress>

TcpClient::TcpClient(const QString &serverAddress, quint16 serverPort,
                     QObject *parent, int retryInterval, int maxRetries)
    : QObject(parent),
    serverAddress(serverAddress),
    serverPort(serverPort),
    retryInterval(retryInterval),
    maxRetries(maxRetries),
    autoReconnect(true)
{
    socket = new QTcpSocket(this);
    reconnectTimer = new QTimer(this);
    reconnectTimer->setSingleShot(true);

    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &TcpClient::onError);
    connect(reconnectTimer, &QTimer::timeout, this, &TcpClient::retryConnection);

    retryCount = 0;

    qDebug() << "[TcpClient] Created for server:" << serverAddress << ":" << serverPort
             << "| Retry interval:" << retryInterval << "ms | Max retries:"
             << (maxRetries < 0 ? "infinite" : QString::number(maxRetries));
}

TcpClient::~TcpClient()
{
    disconnectFromServer(true);
    delete socket;
    delete reconnectTimer;
    qDebug() << "[TcpClient] Destroyed";
}

void TcpClient::connectToServer()
{
    QMutexLocker locker(&connectionMutex);

    if (socket->state() == QAbstractSocket::ConnectingState ||
        socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "[TcpClient] Already connecting or connected to server";
        return;
    }

    qDebug() << "[TcpClient] Connecting to server" << serverAddress << ":" << serverPort;
    connectionTimer.start();
    socket->connectToHost(serverAddress, serverPort);
}

void TcpClient::disconnectFromServer(bool stopRetrying)
{
    QMutexLocker locker(&connectionMutex);

    if (stopRetrying && reconnectTimer->isActive()) {
        reconnectTimer->stop();
        qDebug() << "[TcpClient] Disabling reconnect timer";
    }

    if (socket->state() != QAbstractSocket::UnconnectedState) {
        qDebug() << "[TcpClient] Disconnecting from server";
        socket->disconnectFromHost();
        if (socket->state() != QAbstractSocket::UnconnectedState) {
            socket->waitForDisconnected(1000);
        }
    }
}

qint64 TcpClient::sendMessage(const QString &message)
{
    QMutexLocker locker(&connectionMutex);

    if (socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[TcpClient] Error: Not connected to server. Cannot send message.";
        return -1;
    }

    if (message.isEmpty()) {
        qDebug() << "[TcpClient] Warning: Trying to send empty message";
        return 0;
    }

    qint64 bytesSent = socket->write(message.toUtf8());

    if (bytesSent > 0) {
        qDebug() << "[TcpClient Sent] Size:" << bytesSent << "| Content:" << message;
        emit messageSent(message);
    } else {
        qDebug() << "[TcpClient] Error: Failed to send message";
    }

    return bytesSent;
}

bool TcpClient::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void TcpClient::setAutoReconnect(bool enable)
{
    autoReconnect = enable;
    qDebug() << "[TcpClient] Auto reconnect" << (enable ? "enabled" : "disabled");
}

void TcpClient::setReconnectParams(int interval, int maxRetries)
{
    QMutexLocker locker(&connectionMutex);

    retryInterval = interval;
    this->maxRetries = maxRetries;
    reconnectTimer->setInterval(retryInterval);

    qDebug() << "[TcpClient] Set reconnect params | Interval:" << retryInterval
             << "ms | Max retries:"
             << (maxRetries < 0 ? "infinite" : QString::number(maxRetries));
}

void TcpClient::startReconnectTimer()
{
    QMutexLocker locker(&connectionMutex);

    if (!autoReconnect) {
        qDebug() << "[TcpClient] Auto reconnect disabled, not starting timer";
        return;
    }

    if (maxRetries >= 0 && retryCount >= maxRetries) {
        qDebug() << "[TcpClient] Max retries reached, stopping reconnect attempts";
        return;
    }

    int delay = retryInterval;

    // 指数退避策略
    if (retryCount > 0) {
        delay = qMin(retryInterval * (1 << (retryCount - 1)), 30000); // 最大间隔30秒
    }

    qDebug() << "[TcpClient] Will reconnect in" << delay << "ms (attempt"
             << (retryCount + 1) << "of"
             << (maxRetries < 0 ? "∞" : QString::number(maxRetries)) << ")";

    reconnectTimer->start(delay);
    emit reconnecting(retryCount + 1, delay);
}

void TcpClient::resetReconnectState()
{
    QMutexLocker locker(&connectionMutex);
    retryCount = 0;
    reconnectTimer->stop();
    qDebug() << "[TcpClient] Reconnect state reset";
}

// ========== 私有槽实现 ==========

void TcpClient::onConnected()
{
    qDebug() << "[TcpClient] Successfully connected to server" << serverAddress << ":" << serverPort
             << "in" << connectionTimer.elapsed() << "ms";
    resetReconnectState();
    emit connected();
    emit connectionAttempted(true, "Connection established");
}

void TcpClient::onDisconnected()
{
    qDebug() << "[TcpClient] Disconnected from server";
    emit disconnected();

    // 仅在自动重连启用时才尝试重连
    if (autoReconnect) {
        startReconnectTimer();
    } else {
        qDebug() << "[TcpClient] Auto reconnect disabled";
    }
}

void TcpClient::onReadyRead()
{
    while (socket->bytesAvailable() > 0) {
        QByteArray data = socket->readAll();
        QString message = QString::fromUtf8(data);

        if (!message.isEmpty()) {
            qDebug() << "[TcpClient Received] Size:"
                     << data.size() << "| Content:" << message.trimmed();
            emit messageReceived(message.trimmed());
        }
    }
}

void TcpClient::onError(QAbstractSocket::SocketError socketError)
{
    QString errorStr = socket->errorString();

    qDebug() << "[TcpClient Error]" << errorStr
             << "(Error code:" << socketError << ")";

    emit connectionAttempted(false, errorStr);

    // 连接尝试失败时启动重连
    if (autoReconnect) {
        startReconnectTimer();
    } else {
        qDebug() << "[TcpClient] Auto reconnect disabled";
    }
}

void TcpClient::retryConnection()
{
    QMutexLocker locker(&connectionMutex);

    // 检查当前是否已经连接或正在连接
    if (socket->state() == QAbstractSocket::ConnectedState ||
        socket->state() == QAbstractSocket::ConnectingState) {
        qDebug() << "[TcpClient] Skipping retry - already connected or connecting";
        return;
    }

    if (maxRetries >= 0 && retryCount >= maxRetries) {
        qDebug() << "[TcpClient] Max retries reached, stopping reconnect attempts";
        return;
    }

    qDebug() << "[TcpClient] Attempting reconnect (" << (retryCount + 1) << ")";
    connectionTimer.restart();
    socket->connectToHost(serverAddress, serverPort);
    retryCount++;
}
