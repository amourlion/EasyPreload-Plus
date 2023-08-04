// test_sockethooker.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <sys/socket.h>

int main() {
    // 创建一个套接字并测试socket函数拦截
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }
    close(sockfd);

    // 创建一个TCP套接字并测试connect函数拦截
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    int result = connect(tcp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (result < 0) {
        perror("connect");
        return EXIT_FAILURE;
    }
    close(tcp_socket);

    // 创建一个UDP套接字并测试bind函数拦截
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in udp_addr;
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(8080);
    udp_addr.sin_addr.s_addr = INADDR_ANY;
    result = bind(udp_socket, (struct sockaddr *)&udp_addr, sizeof(udp_addr));
    if (result < 0) {
        perror("bind");
        return EXIT_FAILURE;
    }
    close(udp_socket);

    // 创建一个TCP套接字并测试listen函数拦截
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in listen_addr;
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(8080);
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    result = bind(server_socket, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
    if (result < 0) {
        perror("bind");
        return EXIT_FAILURE;
    }
    result = listen(server_socket, 5);
    if (result < 0) {
        perror("listen");
        return EXIT_FAILURE;
    }
    close(server_socket);

    // 创建一个TCP套接字并测试accept函数拦截
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_accept_addr;
    server_accept_addr.sin_family = AF_INET;
    server_accept_addr.sin_port = htons(8080);
    server_accept_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    result = connect(client_socket, (struct sockaddr *)&server_accept_addr, sizeof(server_accept_addr));
    if (result < 0) {
        perror("connect");
        return EXIT_FAILURE;
    }

    int accepted_socket = accept(client_socket, NULL, NULL);
    if (accepted_socket < 0) {
        perror("accept");
        return EXIT_FAILURE;
    }
    close(accepted_socket);
    close(client_socket);

    return EXIT_SUCCESS;
}
