#ifndef __CONFIG__
#define __CONFIG__

#include <stdbool.h>

struct config_t;

void config_ctor(struct config_t*);
void config_dtor(struct config_t*);
struct config_t* config_malloc();

int config_get_port(struct config_t*);
bool config_get_plug(struct config_t*);

#endif
