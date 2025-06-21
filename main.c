#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")  // 链接Winsock库

#define PORT_A 12345     // 监听前端的端口
#define PORT_C 65433     // 连接后端的端口
#define BUFFER_SIZE 1024 // 缓冲区大小
#define END_MARKER "<END>" // 结束标记
#define END_MARKER_LEN 5   // 结束标记长度

int main() {
    WSADATA wsa;
    SOCKET sock_a = INVALID_SOCKET;   // 监听前端的套接字
    SOCKET sock_c = INVALID_SOCKET;   // 连接后端的套接字
    struct sockaddr_in server_a, server_c;
    char buffer[BUFFER_SIZE];          // 数据缓冲区
    
    printf("中间层(B)启动...\n");
    printf("监听前端端口: %d\n", PORT_A);
    printf("连接后端端口: %d\n", PORT_C);
    
    // 初始化Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup失败. 错误代码: %d\n", WSAGetLastError());
        return 1;
    }
    
    // 创建监听前端的套接字
    if ((sock_a = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        fprintf(stderr, "创建套接字失败. 错误代码: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    
    // 设置监听套接字选项
    BOOL reuse = TRUE;
    if (setsockopt(sock_a, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) == SOCKET_ERROR) {
        fprintf(stderr, "设置套接字选项失败. 错误代码: %d\n", WSAGetLastError());
        closesocket(sock_a);
        WSACleanup();
        return 1;
    }
    
    // 配置监听地址
    server_a.sin_family = AF_INET;
    server_a.sin_addr.s_addr = INADDR_ANY;
    server_a.sin_port = htons(PORT_A);
    
    // 绑定套接字
    if (bind(sock_a, (struct sockaddr*)&server_a, sizeof(server_a)) == SOCKET_ERROR) {
        fprintf(stderr, "绑定失败. 错误代码: %d\n", WSAGetLastError());
        closesocket(sock_a);
        WSACleanup();
        return 1;
    }
    
    // 开始监听
    if (listen(sock_a, 1) == SOCKET_ERROR) {
        fprintf(stderr, "监听失败. 错误代码: %d\n", WSAGetLastError());
        closesocket(sock_a);
        WSACleanup();
        return 1;
    }
    
    printf("等待前端(A)连接...\n");
    
    // 接受前端连接
    int addr_len = sizeof(server_a);
    SOCKET client_a = INVALID_SOCKET;
    if ((client_a = accept(sock_a, (struct sockaddr*)&server_a, &addr_len)) == INVALID_SOCKET) {
        fprintf(stderr, "接受连接失败. 错误代码: %d\n", WSAGetLastError());
        closesocket(sock_a);
        WSACleanup();
        return 1;
    }
    
    printf("前端(A)已连接!\n");
    
    // 主循环
    while (1) {
        // 接收前端数据
        int bytes_received = recv(client_a, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received == SOCKET_ERROR) {
            fprintf(stderr, "接收数据失败. 错误代码: %d\n", WSAGetLastError());
            break;
        } else if (bytes_received == 0) {
            printf("前端(A)断开连接\n");
            break;
        }
        
        // 添加字符串终止符
        buffer[bytes_received] = '\0';
        printf("接收到前端数据: %s\n", buffer);
        
        // 创建连接后端的套接字
        if ((sock_c = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            fprintf(stderr, "创建后端套接字失败. 错误代码: %d\n", WSAGetLastError());
            break;
        }
        
        // 配置后端地址
        server_c.sin_family = AF_INET;
        server_c.sin_addr.s_addr = inet_addr("127.0.0.1"); // 后端地址
        server_c.sin_port = htons(PORT_C);
        
        // 连接后端
        if (connect(sock_c, (struct sockaddr*)&server_c, sizeof(server_c)) < 0) {
            fprintf(stderr, "连接后端失败. 错误代码: %d\n", WSAGetLastError());
            closesocket(sock_c);
            continue;
        }
        
        printf("已连接后端(C)\n");
        
        // 添加结束标记并发送数据到后端
        char send_buffer[BUFFER_SIZE + END_MARKER_LEN];
        strcpy(send_buffer, buffer);
        strcat(send_buffer, END_MARKER);
        
        if (send(sock_c, send_buffer, strlen(send_buffer), 0) == SOCKET_ERROR) {
            fprintf(stderr, "发送数据到后端失败. 错误代码: %d\n", WSAGetLastError());
            closesocket(sock_c);
            continue;
        }
        
        printf("已发送数据到后端: %s\n", send_buffer);
        
        // 接收后端响应
        char recv_buffer[BUFFER_SIZE] = {0};
        char* end_pos = NULL;
        int total_received = 0;
        
        // 循环接收直到找到结束标记
        while (end_pos == NULL) {
            int bytes_received_c = recv(sock_c, recv_buffer + total_received, 
                                       BUFFER_SIZE - total_received - 1, 0);
            
            if (bytes_received_c == SOCKET_ERROR) {
                fprintf(stderr, "接收后端数据失败. 错误代码: %d\n", WSAGetLastError());
                break;
            } else if (bytes_received_c == 0) {
                printf("后端(C)断开连接\n");
                break;
            }
            
            total_received += bytes_received_c;
            recv_buffer[total_received] = '\0';
            
            // 检查是否包含结束标记
            end_pos = strstr(recv_buffer, END_MARKER);
        }
        
        // 移除结束标记
        if (end_pos != NULL) {
            *end_pos = '\0';
            printf("接收到后端结果: %s\n", recv_buffer);
            
            // 将结果发送回前端
            if (send(client_a, recv_buffer, strlen(recv_buffer), 0) == SOCKET_ERROR) {
                fprintf(stderr, "发送结果到前端失败. 错误代码: %d\n", WSAGetLastError());
            } else {
                printf("已发送结果到前端\n");
            }
        } else {
            fprintf(stderr, "未找到结束标记，数据可能不完整\n");
        }
        
        // 关闭后端连接
        closesocket(sock_c);
        sock_c = INVALID_SOCKET;
    }
    
    // 清理资源
    if (sock_c != INVALID_SOCKET) closesocket(sock_c);
    if (client_a != INVALID_SOCKET) closesocket(client_a);
    if (sock_a != INVALID_SOCKET) closesocket(sock_a);
    WSACleanup();
    
    printf("中间层(B)已停止\n");
    return 0;
}