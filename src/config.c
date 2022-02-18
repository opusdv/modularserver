#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int port;
	bool plug;
} config_t;

config_t* config_malloc() {
	return (config_t*)malloc(sizeof(config_t));
}

void config_ctor(config_t* config) {
	int port = 0;
	const char* port_from_env = getenv("MY_PORT");
	if (port_from_env == NULL) {
		config->port = 2626;
	}
	config->plug = false;
}

void config_dtor(config_t* config) {
	config->port = 0;
}

int config_get_port(config_t* config) {
	return config->port;
}

bool config_get_plug(config_t* config) {
	return config->plug;
}
