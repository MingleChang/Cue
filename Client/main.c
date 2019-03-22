//
//  main.c
//  Client
//
//  Created by gongtao on 2019/2/1.
//

#include "cue.h"
#include "client.h"

struct cue_connect *client;

struct event_base *base;
struct bufferevent *event;
struct bufferevent *io_event;

static void read_callback(struct bufferevent *bev, void *user_data) {
    size_t len = 0;
    size_t length = 0;
    while (1) {
        if (client->head == NULL) {
            client->head = malloc(4);
            memset(client->head, 0, 4);
            length = 4;
            client->head_len = bufferevent_read(bev, client->head, length);
            if (client->head_len < 4) {
                return;
            }else {
                memcpy(&client->buffer_max_len, client->head, client->head_len);
                client->buffer = malloc(client->buffer_max_len);
            }
        }else if (client->head_len < 4) {
            length = 4 - client->head_len;
            len = bufferevent_read(bev, client->head + client->head_len, length);
            client->head_len = client->head_len + len;
            if (client->head_len < 4) {
                return;
            }else {
                memcpy(&client->buffer_max_len, client->head, client->head_len);
                client->buffer = malloc(client->buffer_max_len);
            }
        }else {
            length = client->buffer_max_len - client->buffer_len;
            len = bufferevent_read(bev, client->buffer + client->buffer_len, length);
            client->buffer_len = client->buffer_len + len;
            if (len < length){
                return;
            }else if(client->buffer_len == client->buffer_max_len) {
                printf("recieve => %s\n", client->buffer);
                cue_connect_clear(client);
            }
        }
    }
}
//static void write_callback(struct bufferevent *bev, void *user_data) {
//    
//}
static void error_callback(struct bufferevent *bev, short what, void *user_data) {
    if (what & BEV_EVENT_CONNECTED) {
        return;
    }
    bufferevent_free(bev);
    event_base_loopexit(base, 0);
}

static void io_read_callback(struct bufferevent *bev, void *user_data) {
    char buff[CUE_MAXLINE];
    memset(buff, 0, CUE_MAXLINE);
    size_t len = bufferevent_read(bev, buff, CUE_MAXLINE - 1);
    char data[4 + len];
    memset(data, 0, 4+len);
    memcpy(data, &len, 4);
    memcpy(data+4, buff, len-1);
    bufferevent_write(event, data, 4 + len);
}
//static void io_write_callback(struct bufferevent *bev, void *user_data) {
//
//}
static void io_error_callback(struct bufferevent *bev, short what, void *user_data) {
    
}

int main(int argc, const char * argv[]) {
    printf("Start Client\n");
    struct evdns_base *dns_base;
    base = event_base_new();
    dns_base = evdns_base_new(base, 1);
    event = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    io_event = bufferevent_socket_new(base, STDIN_FILENO, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_socket_connect_hostname(event, dns_base, AF_UNSPEC, "127.0.0.1", 8080);
    bufferevent_setcb(event, read_callback, NULL, error_callback, base);
    bufferevent_enable(event, EV_READ | EV_PERSIST);
//    bufferevent_setwatermark(event, EV_READ, 4, 4);
    bufferevent_setcb(io_event, io_read_callback, NULL, io_error_callback, base);
    bufferevent_enable(io_event, EV_READ | EV_PERSIST);
    client = cue_connect_new(event);
    event_base_dispatch(base);
    event_base_free(base);
    return 0;
}
