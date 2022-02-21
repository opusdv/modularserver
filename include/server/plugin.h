#ifndef __PLUG__
#define __PLUG__

#include <config.h>

typedef void* (*plugin_func)(void*);
struct plugin_t;

void plugin_ctor(struct plugin_t*, struct config_t*);
void plugin_dtor(struct plugin_t*);

struct plugin_t* plugin_malloc();

plugin_func plugin_get_func(struct plugin_t*);

#endif
