#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <config.h>
#include <connection.h>
#include <coreserver.h>
#include <plugin.h>

int main(int argc, const char **argv) {
	struct config_t* config = config_malloc();
	struct connection_t* connection = connection_malloc();
	struct plugin_t* plugin = plugin_malloc();
	struct coreserver_t* coreserver = coreserver_malloc();
	
	config_ctor(config);
	connection_ctor(connection, config);
	plugin_ctor(plugin, config);
	
	coreserver_ctor(coreserver);
	coreserver_set_config(coreserver, config);
	coreserver_set_connection(coreserver, connection);
	coreserver_set_plugin(coreserver, plugin);
	
	coreserver_connectin_start(coreserver);
	
	free(plugin);
	free(config);
	free(connection);
	free(coreserver);
	
	return 0;
}
