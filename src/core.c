#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include <config.h>

typedef struct {
	struct sockaddr_in addr;
	int server_sd;
} socket_t;

socket_t* socket_malloc() {
	return (socket_t*)malloc(sizeof(socket_t));
}

void __socket_bind(int socket_sd, struct sockaddr_in addr) {
	int bind_result = bind(socket_sd, (struct sockaddr*)&addr, sizeof(addr));
	if (bind_result < 0) {
		perror("bind");
		strerror(errno);
		exit(1);
	}
}

void __socket_listen(int socket_sd, int client_count) {
	int lis_result = listen(socket_sd, client_count);
	if (lis_result < 0) {
		perror("list");
		exit(1);
	}
}

void __socket_accept(int socket_sd, struct config_t* config) {
	printf("Connection wait.....\n");
	while(1) {
		int client_sd = accept(socket_sd, NULL, NULL);
		if (client_sd < 0) {
			perror("Accept: ");
			exit(1);
		}
		while (1) {
			send(client_sd, "hi\n", 3, 0);
			break;
		}
		break;
	}
}

void socket_ctor(socket_t* sock, void* config ) {
	struct config_t* conf = (struct config_t*)config;
	struct sockaddr_in addr;
	int server_sd = socket(AF_INET, SOCK_STREAM, 0);
	int client_sd = 0;
	if (server_sd < 0) {
		strerror(errno);
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = config_get_port(conf);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	sock->addr = addr;
	sock->server_sd = server_sd;
	
	__socket_bind(sock->server_sd, sock->addr);
	__socket_listen(sock->server_sd, 2);
	__socket_accept(sock->server_sd, conf);
	
}

void socket_dtor(socket_t* sock) {
	free(sock);
	sock->server_sd = 0;
}

int socket_get_server_sd(socket_t* sock) {
	return sock->server_sd;
}

struct sockaddr_in socket_get_socketadd_in(socket_t* sock) {
	return sock->addr;
}
