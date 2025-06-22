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

SOCKET listenSocket = INVALID_SOCKET; // 修改：添加监听套接字变量

void SafePrint(const char* buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            putchar(buffer[i]);
        } else {
            putchar('.');
        }
    }
}

// 修改：添加线程参数结构体
typedef struct {
    SOCKET from;
    SOCKET to;
    int fromPort;
    int toPort;
} ThreadParam;

DWORD WINAPI ServerToClientThread(LPVOID lpParam) {
    ThreadParam* param = (ThreadParam*)lpParam;
    SOCKET from = param->from;
    SOCKET to = param->to;
    int fromPort = param->fromPort;
    int toPort = param->toPort;
    
    char buffer[BUFFER_SIZE];
    int bytesRead;
    
    while (1) {
        bytesRead = recv(from, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) break;
        
        printf("[port %d SEND]: ", fromPort);
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
        
        int bytesSent = send(to, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;
        
        printf("[port %d RECV]: ", toPort);
        SafePrint(buffer, bytesSent);
        printf(" (%d bytes)\n", bytesSent);
    }
    
    // 关闭套接字
    closesocket(from);
    closesocket(to);
    free(param); // 释放参数内存
    return 0;
}

DWORD WINAPI ClientToServerThread(LPVOID lpParam) {
    ThreadParam* param = (ThreadParam*)lpParam;
    SOCKET from = param->from;
    SOCKET to = param->to;
    int fromPort = param->fromPort;
    int toPort = param->toPort;
    
    char buffer[BUFFER_SIZE];
    int bytesRead;
    
    while (1) {
        bytesRead = recv(from, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) break;
        
        printf("[port %d SEND]: ", fromPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d bytes)\n", bytesRead);
        
        // 删除末尾的<END>标记（如果存在）
        if (bytesRead >= END_MARKER_LEN && 
            memcmp(buffer + bytesRead - END_MARKER_LEN, END_MARKER, END_MARKER_LEN) == 0) {
            bytesRead -= END_MARKER_LEN;  // 移除末尾的<END>标记
            printf("[PROCESS]: Removed <%s> marker\n", END_MARKER);
        }
        
        int bytesSent = send(to, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;
        
        printf("[port %d RECV]: ", toPort);
        SafePrint(buffer, bytesSent);
        printf(" (%d bytes)\n", bytesSent);
    }
    
    // 关闭套接字
    closesocket(from);
    closesocket(to);
    free(param); // 释放参数内存
    return 0;
}

void SetupServer() {
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        printf("server socket() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    // 设置SO_REUSEADDR选项，允许快速重用端口
    int reuse = 1;
    if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) == SOCKET_ERROR) {
        printf("setsockopt(SO_REUSEADDR) failed: %d\n", WSAGetLastError());
    }
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(SERVER_PORT);
    
    if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("bind() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) { // 修改：增加积压连接数
        printf("listen() failed: %d\n", WSAGetLastError());
        exit(1);
    }
    
    printf("Server listening on port %d (external)\n", SERVER_PORT);
}

SOCKET ConnectToTargetServer() {
    // 创建客户端套接字
    SOCKET targetSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (targetSocket == INVALID_SOCKET) {
        printf("client socket() failed: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }
    
    // 设置目标服务器地址
    struct sockaddr_in targetAddr;
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_addr.s_addr = inet_addr(TARGET_SERVER_IP);
    targetAddr.sin_port = htons(TARGET_SERVER_PORT);
    
    // 连接到目标服务器
    printf("Connecting to external server %s:%d...\n", TARGET_SERVER_IP, TARGET_SERVER_PORT);
    if (connect(targetSocket, (struct sockaddr*)&targetAddr, sizeof(targetAddr)) == SOCKET_ERROR) {
        printf("connect() failed: %d\n", WSAGetLastError());
        closesocket(targetSocket);
        return INVALID_SOCKET;
    }
    
    printf("Connected to external server %s:%d\n", TARGET_SERVER_IP, TARGET_SERVER_PORT);
    return targetSocket;
}

int main() {
    WSADATA wsa;
    
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }
    
    // 设置本地服务器（监听12345端口）
    SetupServer();
    
    while (1) { // 修改：添加主循环，持续接受新连接
        struct sockaddr_in clientAddr;
        int addrSize = sizeof(clientAddr);
        
        // 接受客户端连接到本地服务器
        printf("\nWaiting for client on port %d...\n", SERVER_PORT);
        SOCKET clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &addrSize);
        if (clientSocket == INVALID_SOCKET) {
            printf("accept() failed: %d\n", WSAGetLastError());
            continue; // 继续等待下一个连接
        }
        
        // 获取客户端IP地址
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        printf("External client connected from %s:%d to port %d\n", 
               clientIP, ntohs(clientAddr.sin_port), SERVER_PORT);
        
        // 连接到目标服务器
        SOCKET targetSocket = ConnectToTargetServer();
        if (targetSocket == INVALID_SOCKET) {
            closesocket(clientSocket);
            continue; // 继续等待下一个连接
        }
        
        // 创建线程参数
        ThreadParam* param1 = (ThreadParam*)malloc(sizeof(ThreadParam));
        ThreadParam* param2 = (ThreadParam*)malloc(sizeof(ThreadParam));
        
        if (!param1 || !param2) {
            printf("Memory allocation failed\n");
            closesocket(clientSocket);
            closesocket(targetSocket);
            continue;
        }
        
        // 设置线程参数
        param1->from = clientSocket;
        param1->to = targetSocket;
        param1->fromPort = SERVER_PORT;
        param1->toPort = TARGET_SERVER_PORT;
        
        param2->from = targetSocket;
        param2->to = clientSocket;
        param2->fromPort = TARGET_SERVER_PORT;
        param2->toPort = SERVER_PORT;
        
        // 创建转发线程
        HANDLE threads[2];
        threads[0] = CreateThread(NULL, 0, ServerToClientThread, param1, 0, NULL);
        threads[1] = CreateThread(NULL, 0, ClientToServerThread, param2, 0, NULL);
        
        if (threads[0] == NULL || threads[1] == NULL) {
            printf("Failed to create threads\n");
            closesocket(clientSocket);
            closesocket(targetSocket);
            free(param1);
            free(param2);
            continue;
        }
        
        // 等待线程结束（当连接关闭时）
        WaitForMultipleObjects(2, threads, TRUE, INFINITE);
        
        // 关闭线程句柄
        CloseHandle(threads[0]);
        CloseHandle(threads[1]);
        
        printf("Client disconnected. Ready for new connections.\n");
    }
    
    // 清理资源（理论上永远不会到达这里）
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}