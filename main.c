#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // 添加ctype.h头文件用于字符分类函数

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

// 新增函数：格式化表达式为函数调用形式
void FormatExpression(char* buffer, int* bytesRead) {
    int len = *bytesRead;
    int i, j;

    // 情况1: 字母开头后接数字 (如 "mexp1" -> "mexp(1)")
    if (isalpha((unsigned char)buffer[0]) && len > 1) {
        int firstDigit = -1;
        for (i = 1; i < len; i++) {
            if (isdigit((unsigned char)buffer[i])) {
                firstDigit = i;
                break;
            }
        }
        if (firstDigit != -1) {
            // 在第一个数字前插入 '('
            memmove(buffer + firstDigit + 1, buffer + firstDigit, len - firstDigit);
            buffer[firstDigit] = '(';
            len++;
            
            // 在末尾添加 ')'
            if (len < BUFFER_SIZE) {
                buffer[len++] = ')';
                printf("[处理] 格式化为函数调用: %.*s\n", len, buffer);
            } else {
                printf("[警告] 缓冲区不足，无法添加括号\n");
            }
        }
    }
    // 情况2: 数字开头后接字母 (如 "4rec" -> "rec(4)")
    else if (isdigit((unsigned char)buffer[0]) && len > 1) {
        int firstAlpha = -1;
        for (i = 0; i < len; i++) {
            if (isalpha((unsigned char)buffer[i])) {
                firstAlpha = i;
                break;
            }
        }
        if (firstAlpha != -1 && firstAlpha > 0) {
            char temp[BUFFER_SIZE];
            int numLen = firstAlpha;
            int funcLen = len - firstAlpha;
            
            // 重新排序: 函数名 + ( + 数字 + )
            memcpy(temp, buffer + firstAlpha, funcLen);  // 复制函数名
            temp[funcLen] = '(';                       // 添加开括号
            memcpy(temp + funcLen + 1, buffer, numLen); // 复制数字参数
            temp[funcLen + 1 + numLen] = ')';           // 添加闭括号
            
            // 复制回原缓冲区
            int newLen = funcLen + numLen + 2;
            if (newLen <= BUFFER_SIZE) {
                memcpy(buffer, temp, newLen);
                len = newLen;
                printf("[处理] 格式化为函数调用: %.*s\n", len, buffer);
            } else {
                printf("[警告] 缓冲区不足，无法格式化表达式\n");
            }
        }
    }
    
    *bytesRead = len;
}

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
        
        // 打印接收到的原始数据
        printf("[原始接收] 来自端口 %d 的数据: ", fromPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d 字节)\n", bytesRead);
        
        printf("[处理前] 端口 %d SEND: ", fromPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d 字节)\n", bytesRead);
        
        // 删除末尾的等号(=)
        if (bytesRead > 0 && buffer[bytesRead - 1] == '=') {
            bytesRead--; // 移除末尾的等号
            printf("[处理] 移除末尾等号\n");
            
            // 新增：格式化表达式
            FormatExpression(buffer, &bytesRead);
        }
        
        // 添加结束标记
        if (bytesRead + END_MARKER_LEN < BUFFER_SIZE) {
            memcpy(buffer + bytesRead, END_MARKER, END_MARKER_LEN);
            bytesRead += END_MARKER_LEN;
            printf("[处理] 添加 <%s> 标记\n", END_MARKER);
        } else {
            printf("[警告] 缓冲区满，无法添加标记\n");
        }
        
        // 打印处理后数据
        printf("[处理后] 发送到端口 %d 的数据: ", toPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d 字节)\n", bytesRead);
        
        int bytesSent = send(to, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;
        
        printf("[发送完成] 端口 %d RECV: ", toPort);
        SafePrint(buffer, bytesSent);
        printf(" (%d 字节)\n", bytesSent);
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
        
        // 打印接收到的原始数据
        printf("[原始接收] 来自端口 %d 的数据: ", fromPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d 字节)\n", bytesRead);
        
        printf("[处理前] 端口 %d SEND: ", fromPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d 字节)\n", bytesRead);
        
        // 删除末尾的<END>标记（如果存在）
        if (bytesRead >= END_MARKER_LEN && 
            memcmp(buffer + bytesRead - END_MARKER_LEN, END_MARKER, END_MARKER_LEN) == 0) {
            bytesRead -= END_MARKER_LEN;  // 移除末尾的<END>标记
            printf("[处理] 移除 <%s> 标记\n", END_MARKER);
        }
        
        // 打印处理后数据
        printf("[处理后] 发送到端口 %d 的数据: ", toPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d 字节)\n", bytesRead);
        
        int bytesSent = send(to, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;
        
        printf("[发送完成] 端口 %d RECV: ", toPort);
        SafePrint(buffer, bytesSent);
        printf(" (%d 字节)\n", bytesSent);
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
    
    printf("服务器正在监听端口 %d (外部连接)\n", SERVER_PORT);
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
    printf("正在连接到外部服务器 %s:%d...\n", TARGET_SERVER_IP, TARGET_SERVER_PORT);
    if (connect(targetSocket, (struct sockaddr*)&targetAddr, sizeof(targetAddr)) == SOCKET_ERROR) {
        printf("connect() failed: %d\n", WSAGetLastError());
        closesocket(targetSocket);
        return INVALID_SOCKET;
    }
    
    printf("已成功连接到外部服务器 %s:%d\n", TARGET_SERVER_IP, TARGET_SERVER_PORT);
    return targetSocket;
}

int main() {
    WSADATA wsa;
    
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup 失败: %d\n", WSAGetLastError());
        return 1;
    }
    
    // 设置本地服务器（监听12345端口）
    SetupServer();
    
    while (1) { // 修改：添加主循环，持续接受新连接
        struct sockaddr_in clientAddr;
        int addrSize = sizeof(clientAddr);
        
        // 接受客户端连接到本地服务器
        printf("\n正在等待客户端连接端口 %d...\n", SERVER_PORT);
        SOCKET clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &addrSize);
        if (clientSocket == INVALID_SOCKET) {
            printf("accept() 失败: %d\n", WSAGetLastError());
            continue; // 继续等待下一个连接
        }
        
        // 获取客户端IP地址
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        printf("外部客户端已连接: %s:%d 到端口 %d\n", 
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
            printf("内存分配失败\n");
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
            printf("创建线程失败\n");
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
        
        printf("客户端已断开连接。准备接受新连接。\n");
    }
    
    // 清理资源（理论上永远不会到达这里）
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}