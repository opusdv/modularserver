#ifndef __CORESERVER__
#define __CORESERVER__

#include <config.h>
#include <connection.h>
#include <plugin.h>

struct coreserver_t;

struct coreserver_t* coreserver_malloc();

void coreserver_ctor(struct coreserver_t*);
void coreserver_dtor(struct coreserver_t*);

void coreserver_set_config(struct coreserver_t*, struct config_t*);
void coreserver_set_connection(struct coreserver_t*, struct connection_t*);
void coreserver_set_plugin(struct coreserver_t*,  struct plugin_t*);
void coreserver_connectin_start(struct coreserver_t*);



#endif
