//
//  main.c
//  Server
//
//  Created by gongtao on 2019/2/1.
//

#include <stdio.h>
#include <string.h>
#include <event2/dns.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/event_struct.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/buffer_compat.h>
#include <event2/bufferevent_compat.h>
#include <event2/bufferevent_struct.h>

struct connect {
    evutil_socket_t fd;
    struct bufferevent bev;
    unsigned int buffer_length;
    char *buffer;
};

static void read_callback(struct bufferevent *bev, void *user_data) {
    char buffer[2048];
    memset(buffer, 0, 2048);
    size_t n = bufferevent_read(bev, buffer, 2048);
    printf("%s", buffer);
    bufferevent_write(bev, buffer, n);
}
static void write_callback(struct bufferevent *bev, void *user_data) {
    
}
static void error_callback(struct bufferevent *bev, short what, void *user_data) {
    
}
static void listener_callback(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data) {
    struct event_base *base = user_data;
    struct bufferevent *bev;
    
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_callback, write_callback, error_callback, NULL);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
}

int main(int argc, const char * argv[]) {
    int result;
    struct event_base *base;
    struct evconnlistener *listenner;
    struct evutil_addrinfo hints, *res;
    
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