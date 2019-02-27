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

struct cue_list *cue_list_create(void* data);
void cue_list_add(struct cue_list *head, void *data);
void cue_list_insert(struct cue_list *head, void *data, int index);
int cue_list_remove(struct cue_list *head, void *data);
void *cue_list_remove_index(struct cue_list *head, int index);
int cue_list_count(struct cue_list *head);

#endif /* cue_list_h */
