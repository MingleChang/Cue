//
//  connect.h
//  Server
//
//  Created by gongtao on 2019/2/15.
//

#ifndef connect_h
#define connect_h

#include "cue.h"

struct cue_connect {
    int fd;
    struct bufferevent *event;
    
    uint32_t buffer_len;
    void *buffer;
};

struct cue_connect * cue_connect_new(struct bufferevent *bev);
void cue_connect_clear(struct cue_connect *connect);
void cue_connect_free(struct cue_connect *connect);

#endif /* connect_h */
