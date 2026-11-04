#include "list.h"

struct _list_node {
    void *data;
    struct _list_node *next;  
};

typedef struct _list_node s_node;

s_node * list_create(void){
    // s_node *list_node = malloc(sizeof(s_node));
    // if(list_node ==  NULL){
    //     printf("null\n");
    //     return NULL;
    // }
    // list_node->data = NULL;
    // list_node->next = NULL;
    // return list_node;
    return NULL;
}
// donne la data du node
void *list_get_data(s_node *node){
    if(node == NULL) return NULL;
    return node->data;
    
}

void list_set_data(s_node *node,void *data){
    if(node ==NULL) return ;
    node->data = data;
}
//en tete
s_node * list_insert(s_node*head, void *data){
    s_node *node = malloc(sizeof(s_node));
    if(node==NULL) return head;
    node->data = data;
    node->next = head;
    return node;
    
}
//return *p sur le node next
s_node * list_next(s_node *head){
    if(head == NULL) return NULL;
    return head->next;
}
//return head
//insert en queue de liste
s_node *list_append(s_node*head, void *data){
    
    s_node *node = malloc(sizeof(s_node));
    if(node==NULL) return head;

    node->data = data;

    if(head == NULL){
        node->next = NULL;
        return head = node;
        
    }

    s_node *nextN = head;
    while(nextN->next!=NULL){
        nextN = nextN->next;
    
    }
    nextN->next = node;
    node->next = NULL;
    return head;
    
}
//** head pour pouvoir modif sinon *head copie de head
s_node * list_orderedAppend(s_node ** head,int (*compare)(s_node *, void*),void * param){


    s_node *nouv = malloc(sizeof(s_node));
    if(nouv==NULL){
        return *head;
    }
    nouv->data = param;
    nouv->next = NULL;
    
    //parcourir la liste et placer dans l'ordre la donnée a inserer 7,15,19
    if(*head == NULL) {
        *head = nouv;
        return nouv;
    }
    s_node *curr = *head;
    s_node *pres = NULL;

    while(curr!=NULL){
        int res = compare(curr,nouv->data);
        //egaux
        if(res==0){
            
            free(nouv);
		    return *head;

        }//param < au node 
        else if(res>=1){
            nouv->next = curr;
        
            if(pres == NULL){
                *head = nouv;
            }else{
                pres->next = nouv;   
            }
            return *head;
        }//param > au node
        
        else{
            
            pres = curr;
            curr =curr->next;
        }
       
        
    }
     pres->next = nouv;
    return *head;
}

//return nouvelle tete
//supp premiere instance dans la liste
s_node * list_remove(s_node *head, void *data){
    s_node *pres = NULL;
    s_node *n_actuel = head;
    while(n_actuel != NULL){
        if(list_get_data(n_actuel) == data){
            if(pres == NULL){            /* c'est la tête */
                s_node *nouvHead = n_actuel->next;
                free(n_actuel);
                return nouvHead;
            }
            pres->next = n_actuel->next;
            free(n_actuel);
            return head;
        }
        pres = n_actuel;
        n_actuel = n_actuel->next;
    }
    return head;
}
//sup la tete
//return nouvelle tete
s_node * list_headRemove(s_node*head){
    if(head == NULL) return NULL;
    s_node *headNouv = head->next;
    free(head);
    return headNouv;
}
//pas de free des donnees
void list_destroy(s_node*head){
    while(head!=NULL){
        head = list_headRemove(head);
    }
}