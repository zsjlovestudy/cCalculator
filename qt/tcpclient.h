// tcpclient.h
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QElapsedTimer>
#include <QMutex>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    /**
     * 构造函数
     * @param serverAddress 服务器IP地址
     * @param serverPort 服务器端口
     * @param parent 父对象
     * @param retryInterval 重试间隔(毫秒)
     * @param maxRetries 最大重试次数(-1表示无限重试)
     */
    explicit TcpClient(const QString &serverAddress, quint16 serverPort,
                       QObject *parent = nullptr,
                       int retryInterval = 5000,
                       int maxRetries = -1);

    ~TcpClient();

    /**
     * 启动连接，如果未连接则立即尝试连接
     * 如果已连接或正在连接中，则忽略
     */
    void connectToServer();

    /**
     * 断开与服务器的连接
     * @param stopRetrying 是否停止重连尝试
     */
    void disconnectFromServer(bool stopRetrying = true);

    /**
     * 发送消息到服务器
     * @param message 要发送的消息
     * @return 实际发送的字节数，失败返回-1
     */
    qint64 sendMessage(const QString &message);

    /**
     * 获取当前连接状态
     * @return true表示已连接，false表示未连接
     */
    bool isConnected() const;

    /**
     * 设置是否启用自动重连
     */
    void setAutoReconnect(bool enable);

    /**
     * 设置重连参数
     * @param interval 重试间隔(毫秒)
     * @param maxRetries 最大重试次数(-1表示无限重试)
     */
    void setReconnectParams(int interval, int maxRetries = -1);

signals:
    void connected();  // 连接建立信号
    void disconnected();  // 连接断开信号
    void messageSent(const QString &message);  // 消息发送信号
    void messageReceived(const QString &message);  // 消息接收信号
    void connectionAttempted(bool success, const QString &message);  // 连接尝试结果信号
    void reconnecting(int attempt, int nextRetryMs);  // 即将重连信号

private slots:
    void onConnected();  // 连接成功时的处理
    void onDisconnected();  // 连接断开时的处理
    void onReadyRead();  // 接收到数据时的处理
    void onError(QAbstractSocket::SocketError socketError);  // 错误发生时的处理
    void retryConnection();  // 重连尝试

private:
    void startReconnectTimer();  // 启动重连定时器
    void resetReconnectState();  // 重置重连状态

    QString serverAddress;   // 服务器地址
    quint16 serverPort;      // 服务器端口
    QTcpSocket *socket;      // TCP套接字对象

    QTimer *reconnectTimer;  // 重连定时器
    int retryInterval;       // 重试间隔(毫秒)
    int maxRetries;          // 最大重试次数(-1表示无限重试)
    int retryCount;          // 当前重试计数

    bool autoReconnect;      // 是否启用自动重连
    QElapsedTimer connectionTimer;  // 连接计时器

    QMutex connectionMutex;  // 连接状态互斥锁
};

#endif // TCPCLIENT_H
