#ifndef __CORE__
#define __CORE__

struct socket_t;

void socket_ctor(struct socket_t*, void* config);
void socket_dtor(struct socket_t*);
struct socket_t* socket_malloc();

int socket_get_server_sd(struct socket_t*);
struct sockaddr_in socket_get_socketadd_in(struct socket_t*);

#endif
