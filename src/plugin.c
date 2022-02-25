#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <config.h>
#include <sys/socket.h>
#include <dlfcn.h>

typedef struct {
	void* (*func)(void*);
} plugin_t;

void* __plugin_default_func(void* arg) {
	int* num = (int*)arg;
	printf("%d\n", num);
	int client_sd = *num;
	
	while(1) {
		send(client_sd, "Hi\n", 3, 0);
		break;
	}

	return arg;
}

void plugin_ctor(plugin_t* plugin, void* config) {
	struct config_t* conf = (struct config_t*)config;
	if (config_get_plug(conf)) {
		void *hdl = dlopen("./lib/libtest.so", RTLD_LAZY);
		if (hdl == NULL) {
			perror("dlopen");
			exit(1);
		}
		plugin->func = (void* (*)(void*))dlsym(hdl, "plugin_func");
		if (plugin->func == NULL) {
			perror("dlsyn");
			exit(1);
		}
		
	} else {
		plugin->func = __plugin_default_func;
	}
}

void plugin_dror(plugin_t* plugin) {
	
}

plugin_t* plugin_malloc() {
	return (plugin_t*)malloc(sizeof(plugin_t));
}

void* (*plugin_get_func(plugin_t* plugin))(void*) {
	return plugin->func;
}

