#ifndef __CONNECTION__
#define __CONNECTION__

struct connection_t;

void connection_ctor(struct connection_t*, void* config);
void connection_dtor(struct connection_t*);
struct connection_t* connection_malloc();

int connection_get_server_sd(struct connection_t*);
struct sockaddr_in connection_get_socketadd_in(struct connection_t*);

#endif
