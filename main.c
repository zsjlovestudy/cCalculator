#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 12345      // 本地服务器端口（供外部客户端连接）
#define TARGET_SERVER_IP "127.0.0.1"  // 外部服务器IP
#define TARGET_SERVER_PORT 65433     // 外部服务器端口
#define BUFFER_SIZE 4096
#define END_MARKER "<END>"
#define END_MARKER_LEN 5  // "<END>"的长度

SOCKET serverSocket = INVALID_SOCKET;
SOCKET clientSocket = INVALID_SOCKET;

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
        
        // 删除末尾的等号(=)
        if (bytesRead > 0 && buffer[bytesRead - 1] == '=') {
            bytesRead--; // 移除末尾的等号
            printf("[PROCESS]: Removed trailing '=' character\n");
        }
        
        // 添加结束标记
        if (bytesRead + END_MARKER_LEN < BUFFER_SIZE) {
            memcpy(buffer + bytesRead, END_MARKER, END_MARKER_LEN);
            bytesRead += END_MARKER_LEN;
            printf("[PROCESS]: Added <%s> marker\n", END_MARKER);
        } else {
            printf("[WARNING]: Buffer full, cannot add marker\n");
        }
        
        int bytesSent = send(clientSocket, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;
        
        printf("[port %d RECV]: ", TARGET_SERVER_PORT);
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
        
        printf("[port %d SEND]: ", TARGET_SERVER_PORT);
        SafePrint(buffer, bytesRead);
        printf(" (%d bytes)\n", bytesRead);
        
        // 修改点：删除末尾的<END>标记（如果存在）
        if (bytesRead >= END_MARKER_LEN && 
            memcmp(buffer + bytesRead - END_MARKER_LEN, END_MARKER, END_MARKER_LEN) == 0) {
            bytesRead -= END_MARKER_LEN;  // 移除末尾的<END>标记
            printf("[PROCESS]: Removed <%s> marker\n", END_MARKER);
        }
        
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
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(SERVER_PORT);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("bind() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        printf("listen() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    printf("Server listening on port %d (external)\n", SERVER_PORT);
}

void ConnectToTargetServer() {
    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        printf("client socket() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    // 设置目标服务器地址
    struct sockaddr_in targetAddr;
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_addr.s_addr = inet_addr(TARGET_SERVER_IP);
    targetAddr.sin_port = htons(TARGET_SERVER_PORT);
    
    // 连接到目标服务器
    printf("Connecting to external server %s:%d...\n", TARGET_SERVER_IP, TARGET_SERVER_PORT);
    if (connect(clientSocket, (struct sockaddr*)&targetAddr, sizeof(targetAddr)) == SOCKET_ERROR) {
        printf("connect() failed: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        exit(1);
    }
    
    printf("Connected to external server %s:%d\n", TARGET_SERVER_IP, TARGET_SERVER_PORT);
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
    
    // 设置本地服务器（监听12345端口）
    SetupServer();
    
    // 连接到目标服务器（外部65433端口）
    ConnectToTargetServer();
    
    // 接受客户端连接到本地服务器
    printf("Waiting for client on port %d...\n", SERVER_PORT);
    SOCKET clientConnection = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
    if (clientConnection == INVALID_SOCKET) {
        printf("accept() failed: %d\n", WSAGetLastError());
        return 1;
    }
    
    // 获取客户端IP地址
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    printf("External client connected from %s:%d to port %d\n", 
           clientIP, ntohs(clientAddr.sin_port), SERVER_PORT);
    
    serverSocket = clientConnection;  // 使用接受的连接
    
    // 创建转发线程
    threads[0] = CreateThread(NULL, 0, ServerToClientThread, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, ClientToServerThread, NULL, 0, NULL);
    
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);
    
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
    closesocket(serverSocket);
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}