//
//  main.c
//  Server
//
//  Created by gongtao on 2019/2/1.
//

#include "cue.h"
#include "server.h"

struct event_base *base;
struct evconnlistener *listenner;
struct cue_list *clients;

static void read_callback(struct bufferevent *bev, void *user_data) {
    char buffer[CUE_MAXLINE];
    memset(buffer, 0, CUE_MAXLINE);
    size_t n = bufferevent_read(bev, buffer, CUE_MAXLINE - 1);
    printf("%s", buffer);
    bufferevent_write(bev, buffer, n);
}
static void write_callback(struct bufferevent *bev, void *user_data) {
}
static void error_callback(struct bufferevent *bev, short what, void *user_data) {
    struct cue_connect *connect = (struct cue_connect *)user_data;
    cue_list_remove(clients, connect);
    if (connect != NULL) {
        cue_connect_free(connect);
    }else {
        bufferevent_free(bev);
    }
}
static void listener_callback(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data) {
    struct event_base *base = user_data;
    struct bufferevent *bev;
    
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    struct cue_connect *connect = cue_connect_new(bev);
    bufferevent_setcb(bev, read_callback, write_callback, error_callback, connect);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
    cue_list_add(clients, connect);
}

int main(int argc, const char * argv[]) {
    int result;
    struct evutil_addrinfo hints, *res;
    clients = cue_list_create(NULL);
    base = event_base_new();
    bzero(&hints, sizeof(struct evutil_addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    result = evutil_getaddrinfo(NULL, "8080", &hints, &res);
    do {
        listenner = evconnlistener_new_bind(base, listener_callback, (void *)base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1, res->ai_addr, res->ai_addrlen);
        if (listenner) {
            break;
        }
    }while ((res = res->ai_next) != NULL);
    event_base_dispatch(base);
    event_base_free(base);
    evconnlistener_free(listenner);
    return 0;
}
