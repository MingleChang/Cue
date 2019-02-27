//
//  connect.c
//  Server
//
//  Created by gongtao on 2019/2/15.
//

#include "connect.h"

struct cue_connect * cue_connect_new(struct bufferevent *bev) {
    struct cue_connect *connect = (struct cue_connect *)malloc(sizeof(struct cue_connect));
    memset(connect, 0, sizeof(struct cue_connect));
    connect->fd = bufferevent_getfd(bev);
    connect->event = bev;
    return connect;
}

void cue_connect_clear(struct cue_connect *connect) {
    connect->buffer_len = 0;
    if (connect->buffer != NULL) {
        free(connect->buffer);
        connect->buffer = NULL;
    }
}

void cue_connect_free(struct cue_connect *connect) {
    cue_connect_clear(connect);
    if (connect->event != NULL) {
        bufferevent_free(connect->event);
        connect->event = NULL;
    }
    free(connect);
    
}
