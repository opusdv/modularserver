#ifndef __PLUG__
#define __PLUG__

typedef void (*plugin_func)(void*);
struct plugin_t;

void plugin_ctor(struct plugin_t*);
void plugin_dtor(struct plugin_t*);

struct plugin_t* plugin_malloc();

#endif
