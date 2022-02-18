#include <stdio.h>
#include <netinet/in.h>


#include <config.h>
#include <core.h>
#include <plugin.h>

int main(int argc, const char **argv) {
	struct config_t* config = config_malloc();
	struct socket_t* sock = socket_malloc();
	
	config_ctor(config);
	socket_ctor(sock, config);
	
	return 0;
}
