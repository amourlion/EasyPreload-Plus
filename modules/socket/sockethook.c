#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int (*original_socket)(int domain, int type, int protocol);
int (*original_connect)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int (*original_bind)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int (*original_listen)(int sockfd, int backlog);
int (*original_accept)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int socket(int domain, int type, int protocol) {
    original_socket = dlsym(RTLD_NEXT, "socket");
    if (original_socket == NULL) {
        perror("dlsym");
        exit(EXIT_FAILURE);
    }

    printf("Intercepted socket call.\n");

    return original_socket(domain, type, protocol);
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    original_connect = dlsym(RTLD_NEXT, "connect");
    if (original_connect == NULL) {
        perror("dlsym");
        exit(EXIT_FAILURE);
    }

    printf("Intercepted connect call.\n");

    return original_connect(sockfd, addr, addrlen);
}

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    original_bind = dlsym(RTLD_NEXT, "bind");
    if (original_bind == NULL) {
        perror("dlsym");
        exit(EXIT_FAILURE);
    }

    printf("Intercepted bind call.\n");

    return original_bind(sockfd, addr, addrlen);
}

int listen(int sockfd, int backlog) {
    original_listen = dlsym(RTLD_NEXT, "listen");
    if (original_listen == NULL) {
        perror("dlsym");
        exit(EXIT_FAILURE);
    }

    printf("Intercepted listen call.\n");

    return original_listen(sockfd, backlog);
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    original_accept = dlsym(RTLD_NEXT, "accept");
    if (original_accept == NULL) {
        perror("dlsym");
        exit(EXIT_FAILURE);
    }

    printf("Intercepted accept call.\n");

    return original_accept(sockfd, addr, addrlen);
}
