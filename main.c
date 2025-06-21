#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT1 12345
#define PORT2 65433
#define BUFFER_SIZE 4096

SOCKET client1 = INVALID_SOCKET;
SOCKET client2 = INVALID_SOCKET;

// 安全打印函数：非可打印字符替换为点
void SafePrint(const char* buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            putchar(buffer[i]);
        } else {
            putchar('.');
        }
    }
}

DWORD WINAPI ForwardThread(LPVOID data) {
    SOCKET src = ((SOCKET*)data)[0];
    SOCKET dst = ((SOCKET*)data)[1];
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // 确定端口信息
    int srcPort = (src == client1) ? PORT1 : PORT2;
    int dstPort = (dst == client1) ? PORT1 : PORT2;

    while (1) {
        // 接收数据
        bytesRead = recv(src, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) break;

        // 打印接收信息
        printf("[Port %d SEND]: ", srcPort);
        SafePrint(buffer, bytesRead);
        printf(" (%d bytes)\n", bytesRead);

        // 发送数据
        int bytesSent = send(dst, buffer, bytesRead, 0);
        if (bytesSent <= 0) break;

        // 打印发送信息
        printf("[Port %d RECV]: ", dstPort);
        SafePrint(buffer, bytesSent);
        printf(" (%d bytes)\n", bytesSent);
    }

    closesocket(src);
    closesocket(dst);
    return 0;
}

void SetupServer(SOCKET* server, int port) {
    *server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*server == INVALID_SOCKET) {
        printf("socket() failed with %d\n", WSAGetLastError());
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(port);

    if (bind(*server, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf("bind() on port %d failed with %d\n", port, WSAGetLastError());
        exit(1);
    }

    if (listen(*server, 1) == SOCKET_ERROR) {
        printf("listen() failed with %d\n", WSAGetLastError());
        exit(1);
    }

    printf("Server listening on port %d\n", port);
}

int main() {
    WSADATA wsa;
    SOCKET server1, server2;
    struct sockaddr_in addr;
    int addrSize = sizeof(addr);
    HANDLE threads[2];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    SetupServer(&server1, PORT1);
    SetupServer(&server2, PORT2);

    printf("Waiting for client on port %d...\n", PORT1);
    client1 = accept(server1, (struct sockaddr*)&addr, &addrSize);
    if (client1 == INVALID_SOCKET) {
        printf("accept() failed: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Client connected to port %d\n", PORT1);

    printf("Waiting for client on port %d...\n", PORT2);
    client2 = accept(server2, (struct sockaddr*)&addr, &addrSize);
    if (client2 == INVALID_SOCKET) {
        printf("accept() failed: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Client connected to port %d\n", PORT2);

    closesocket(server1);
    closesocket(server2);

    SOCKET thread1Data[2] = {client1, client2};
    SOCKET thread2Data[2] = {client2, client1};

    threads[0] = CreateThread(NULL, 0, ForwardThread, thread1Data, 0, NULL);
    threads[1] = CreateThread(NULL, 0, ForwardThread, thread2Data, 0, NULL);

    WaitForMultipleObjects(2, threads, TRUE, INFINITE);
    
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
    WSACleanup();
    return 0;
}