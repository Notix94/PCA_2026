#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _list_node;
typedef struct _list_node s_node;
s_node * list_create(void);
void * list_get_data(const s_node *node);
void list_set_data(s_node * node, void *data);
s_node * list_insert(s_node*head, void *data);
s_node *list_append(s_node*head, void *data);
s_node * list_orderedAppend(s_node ** head,
                            int (*compare)(s_node *, void*)
                            ,void * param);
s_node * list_next(const s_node* head);
s_node * list_remove(s_node *head,void *data);
s_node * list_headRemove(s_node*head);
void list_destroy(s_node*head);
#endif 