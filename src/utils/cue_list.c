//
//  cue_list.c
//  Server
//
//  Created by gongtao on 2019/2/18.
//

#include "cue_list.h"
#include "cue.h"
struct cue_list *cue_list_create(void* data) {
    struct cue_list *node = (struct cue_list *)malloc(sizeof(struct cue_list));
    memset(node, 0, sizeof(struct cue_list));
    node->data = data;
    return node;
}

void cue_list_add(struct cue_list *head, void *data) {
    struct cue_list *temp = head;
    struct cue_list *node = cue_list_create(data);
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = node;
}

void cue_list_insert(struct cue_list *head, void *data, int index) {
    struct cue_list *temp = head;
    struct cue_list *node = cue_list_create(data);
    int i = 0;
    while (temp) {
        if (i == index) {
            struct cue_list *next = temp->next;
            temp->next = node;
            node->next = next;
            break;
        }else if (temp->next == NULL) {
            temp->next = node;
            break;
        }
        temp = temp->next;
        ++i;
    }
}

int cue_list_remove(struct cue_list *head, void *data) {
    struct cue_list *temp = head;
    struct cue_list *node = NULL;
    int i = 0;
    while (temp->next) {
        if (temp->next->data == data) {
            node = temp->next;
            temp->next = temp->next->next;
            break;
        }
        temp = temp->next;
        ++i;
    }
    if (node != NULL) {
        free(node);
    }
    return i;
}

void *cue_list_remove_index(struct cue_list *head, int index) {
    struct cue_list *temp = head;
    struct cue_list *node = NULL;
    for (int i = 0; i <= index; i++) {
        if (temp->next == NULL) {
            return NULL;
        }
        if (i == index) {
            node = temp->next;
            temp->next = node->next;
            void *data = node->data;
            free(node);
            return data;
        }
        temp = temp->next;
    }
    return NULL;
}

int cue_list_count(struct cue_list *head) {
    int count = 0;
    struct cue_list *temp = head->next;
    while (temp) {
        temp = temp->next;
        count ++;
    }
    return count;
}
