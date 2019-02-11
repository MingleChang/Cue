//
//  main.c
//  Client
//
//  Created by gongtao on 2019/2/1.
//

#include <stdio.h>
#include <unistd.h>
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

static void read_callback(struct bufferevent *bev, void *user_data) {
    
}
static void write_callback(struct bufferevent *bev, void *user_data) {
    
}
static void error_callback(struct bufferevent *bev, short what, void *user_data) {
    
}

int main(int argc, const char * argv[]) {
    printf("hello\n");
    int result;
    struct event_base *base;
    struct evdns_base *dns_base;
    struct bufferevent *event;
    struct bufferevent *inevent;
    base = event_base_new();
    dns_base = evdns_base_new(base, 1);
    event = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    inevent = bufferevent_socket_new(base, STDIN_FILENO, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_socket_connect_hostname(event, dns_base, AF_UNSPEC, "127.0.0.1", 8080);
    bufferevent_setcb(event, read_callback, NULL, error_callback, base);
    bufferevent_enable(event, EV_READ | EV_PERSIST);
    event_base_dispatch(base);
    event_base_free(base);
    bufferevent_free(event);
    return 0;
}
