#include <stdlib.h>
#include <config.h>

typedef struct {
	void* (*pf)(void*);
} plugin_t;

void* __plugin_default_func(void* arg) {
	return arg;
	
}

void plugin_ctor(plugin_t* plugin, void* config) {
	struct config_t* conf = (struct config_t*)config;
	if (config_get_plug(conf)) {
		plugin->pf = NULL;
	} else {
		plugin->pf = __plugin_default_func;
	}
}

void plugin_dror(plugin_t* plugin) {
	
}

plugin_t* plugin_malloc() {
	return (plugin_t*)malloc(sizeof(plugin_t));
}
