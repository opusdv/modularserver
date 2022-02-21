#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netinet/in.h>

#include <config.h>
#include <plugin.h>
#include <connection.h>


typedef struct {
	bool state;
	struct config_t* config;
	struct connection_t* connection;
	struct plugin_t* plugin;
} coreserver_t;

coreserver_t* coreserver_malloc() {
	return (coreserver_t*)malloc(sizeof(coreserver_t));
}

void coreserver_ctor(coreserver_t* coreserver) {
	coreserver->state = true;
}

void coreserver_dtor(coreserver_t* coreserver) {
	coreserver->state = false;
}

void coreserver_set_config(coreserver_t* coreserver, void* config) {
	struct config_t* conf = (struct config_t*)config;
	
	coreserver->config = conf;
}

void coreserver_set_connection(coreserver_t* coreserver, void* connection) {
	struct connection_t* conn = (struct connection_t*)connection;	

	coreserver->connection = conn;
}

void coreserver_set_plugin(coreserver_t* coreserver, void* plugin) {
	struct plugin_t* plug = (struct plugin_t*)plugin;
	
	coreserver->plugin = plug;
}

void __coreserver_connection_listen(int socket_sd, int client_count) {
	int lis_result = listen(socket_sd, client_count);
	if (lis_result < 0) {
		perror("listen");
		exit(1);
	}
	
	printf("Socket listen success\n");
}

void __coreserver_connection_accept(int socket_sd, struct plugin_t* plugin) {
	printf("Connection wait......\n");
	while (1) {
		int client_sd = accept(socket_sd, NULL, NULL);
		if (client_sd < 0) {
			perror("accept");
			exit(1);
		}

		printf("Client accept success\n");
		
		void* (*func)(void*) = plugin_get_func(plugin);
		
		int* cd = &client_sd;
		func(cd);

		break;
	}
}

void coreserver_connectin_start(coreserver_t* coreserver) {
	struct connection_t* conn = (struct connection_t*)coreserver->connection;
	struct plugin_t* plug = (struct plugin_t*)coreserver->plugin;
	struct config_t* conf = coreserver->config;
	int server_sd = connection_get_server_sd(conn);

	__coreserver_connection_listen(server_sd, 1);
	__coreserver_connection_accept(server_sd, plug);
}
