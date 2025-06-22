#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 12345
#define CLIENT_PORT 65433
#define TARGET_SERVER_IP "127.0.0.1"
#define TARGET_SERVER_PORT 8888
#define BUFFER_SIZE 4096
#define END_MARKER "<END>"

SOCKET serverSocket = INVALID_SOCKET;
SOCKET clientSocket = INVALID_SOCKET;
SOCKET targetSocket = INVALID_SOCKET;

void SafePrint(const char* buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            putchar(buffer[i]);
        } else {
            putchar('.');
        }
    }
}

DWORD WINAPI ServerToClientThread(LPVOID lpParam) {
    char buffer[BUFFER_SIZE];
    int bytesRead;
    
    while (1) {
        bytesRead = recv(serverSocket, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) break;
        
        printf("[port %d SEND]: ", SERVER_PORT);
        SafePrint(buffer, bytesRead);
        printf(" (%d bytes)\n", bytesRead);
        
        // 添加结束标记
        if (bytesRead + strlen(END_MARKER) < BUFFER_SIZE) {
            memcpy(buffer + bytesRead, END_MARKER, strlen(END_MARKER));
            bytesRead += strlen(END_MARKER);
            printf("[PROCESS]: Added <%s> marker\n", END_MARKER);
        } else {
            printf("[WARNING]: Buffer full, cannot add marker\n");
        }
        
        int bytesSent = send(clientSocket, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;
        
        printf("[port %d RECV]: ", CLIENT_PORT);
        SafePrint(buffer, bytesSent);
        printf(" (%d bytes)\n", bytesSent);
    }
    
    closesocket(serverSocket);
    closesocket(clientSocket);
    return 0;
}

DWORD WINAPI ClientToServerThread(LPVOID lpParam) {
    char buffer[BUFFER_SIZE];
    int bytesRead;
    
    while (1) {
        bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) break;
        
        printf("[port %d SEND]: ", CLIENT_PORT);
        SafePrint(buffer, bytesRead);
        printf(" (%d bytes)\n", bytesRead);
        
        int bytesSent = send(serverSocket, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;
        
        printf("[port %d RECV]: ", SERVER_PORT);
        SafePrint(buffer, bytesSent);
        printf(" (%d bytes)\n", bytesSent);
    }
    
    closesocket(clientSocket);
    closesocket(serverSocket);
    return 0;
}

void SetupServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        printf("server socket() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serverAddr.sin_port = htons(SERVER_PORT);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("bind() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        printf("listen() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    printf("Server listening on port %d\n", SERVER_PORT);
}

void ConnectToTargetServer() {
    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        printf("client socket() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    // 绑定到指定客户端端口
    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    clientAddr.sin_port = htons(CLIENT_PORT);
    
    if (bind(clientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR) {
        printf("client bind() failed: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        exit(1);
    }
    
    // 设置目标服务器地址
    struct sockaddr_in targetAddr;
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_addr.s_addr = inet_addr(TARGET_SERVER_IP);
    targetAddr.sin_port = htons(TARGET_SERVER_PORT);
    
    // 连接到目标服务器
    printf("Client connecting to %s:%d...\n", TARGET_SERVER_IP, TARGET_SERVER_PORT);
    if (connect(clientSocket, (struct sockaddr*)&targetAddr, sizeof(targetAddr)) == SOCKET_ERROR) {
        printf("connect() failed: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        exit(1);
    }
    
    printf("Client connected from port %d to %s:%d\n", 
           CLIENT_PORT, TARGET_SERVER_IP, TARGET_SERVER_PORT);
}

int main() {
    WSADATA wsa;
    HANDLE threads[2];
    struct sockaddr_in clientAddr;
    int addrSize = sizeof(clientAddr);
    
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }
    
    // 设置本地服务器
    SetupServer();
    
    // 连接到目标服务器
    ConnectToTargetServer();
    
    // 接受客户端连接到本地服务器
    printf("Waiting for client on port %d...\n", SERVER_PORT);
    SOCKET clientConnection = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
    if (clientConnection == INVALID_SOCKET) {
        printf("accept() failed: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Client connected to server port %d\n", SERVER_PORT);
    serverSocket = clientConnection;  // 使用接受的连接
    
    // 创建转发线程
    threads[0] = CreateThread(NULL, 0, ServerToClientThread, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, ClientToServerThread, NULL, 0, NULL);
    
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);
    
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
    WSACleanup();
    return 0;
}