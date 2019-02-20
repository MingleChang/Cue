//
//  cue_list.h
//  Server
//
//  Created by gongtao on 2019/2/18.
//

#ifndef cue_list_h
#define cue_list_h

#include <stdio.h>

struct cue_list {
    void *data;
    struct cue_list *next;
};

#endif /* cue_list_h */
