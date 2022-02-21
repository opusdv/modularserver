#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include <config.h>
#include <plugin.h>

typedef struct {
	struct sockaddr_in addr;
	int server_sd;
	int client_sd;
} connection_t;

connection_t* connection_malloc() {
	return (connection_t*)malloc(sizeof(connection_t));
}

void __connection_bind(int socket_sd, struct sockaddr_in addr) {
	int bind_result = bind(socket_sd, (struct sockaddr*)&addr, sizeof(addr));
	if (bind_result < 0) {
		perror("bind");
		strerror(errno);
		exit(1);
	}
	
	printf("Socket binding success\n");
}

void connection_ctor(connection_t* conn, void* config) {
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
	
	conn->addr = addr;
	conn->server_sd = server_sd;

	__connection_bind(conn->server_sd, conn->addr);
}

int connection_get_server_sd(connection_t* conn) {
	return conn->server_sd;
}
