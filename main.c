#include "list.h"
#include "testListHelpers.h"


static int nb_tests = 0, nb_echecs = 0;

//func de test pour list
#define TEST_LIST(head, attendu)                                        \
    do {                                                                  \
        nb_tests++;                                                       \
        if (!check_list_state((head), node_int_to_string, (attendu))) {   \
            nb_echecs++;                                                  \
            fprintf(stderr, "echec ligne %d (%s)\n", __LINE__, __func__); \
        }                                                                 \
    } while (0)


int compare_int(s_node *node, void *param)
{
    int n = *(int *) list_get_data(node);
    int par = *(int *) param;
    if (n < par) return -1;     // noeud plus petit 
    if (n > par) return 1;      // noeud plus grand
    return 0;
}

static void test_liste_create(void){
    s_node *list = list_create();
    TEST_LIST(list,"null");
    list_destroy(list);
}
static void test_insert(void){
    int a = 1, b =2 ;
    s_node *list = list_create();
    list= list_insert(list,&a);
    TEST_LIST(list,"1 -> null");
    list= list_insert(list,&b);
    TEST_LIST(list,"2 -> 1 -> null");
    list_destroy(list);
}
static void test_append(void) {
    int a = 1, b = 2, c = 3;
    s_node *list = list_create();
    list = list_append(list, &a);                 
    TEST_LIST(list, "1 -> null");

    list = list_append(list, &b);
    list = list_append(list, &c);
    TEST_LIST(list, "1 -> 2 -> 3 -> null");
    list_destroy(list);
}

static void test_remove(void) {
    int a = 1, b = 2, c = 3, absent = 99;
    s_node *list = list_create();
    list = list_remove(list, &a);           
    TEST_LIST(list, "null");

    list = list_append(list, &a);
    list = list_append(list, &b);
    list = list_append(list, &c);

    list = list_remove(list, &absent);            
    TEST_LIST(list, "1 -> 2 -> 3 -> null");
    list = list_remove(list, &b);                 
    TEST_LIST(list, "1 -> 3 -> null");
    list = list_remove(list, &c);                 
    TEST_LIST(list, "1 -> null");
    list = list_remove(list, &a);                 
    TEST_LIST(list, "null");
    list_destroy(list);
}

static void test_head_remove(void) {
    int a = 1, b = 2;
    s_node *l = list_create();
    l = list_headRemove(l);                 
    TEST_LIST(l, "null");

    l = list_append(l, &a);
    l = list_append(l, &b);
    l = list_headRemove(l);
    TEST_LIST(l, "2 -> null");

    l = list_headRemove(l);
    TEST_LIST(l, "null");
    list_destroy(l);
}

static void test_ordered_append(void) {
    int v1 = 1, v4 = 4, v9 = 9, v15 = 15, v20 = 20;
    s_node *list = list_create();
    list = list_orderedAppend(&list, compare_int, &v9);    
    TEST_LIST(list, "9 -> null");
    list = list_orderedAppend(&list, compare_int, &v4);    
    TEST_LIST(list, "4 -> 9 -> null");
    list = list_orderedAppend(&list, compare_int, &v15);   
    TEST_LIST(list, "4 -> 9 -> 15 -> null");
    list = list_orderedAppend(&list, compare_int, &v20);
    TEST_LIST(list, "4 -> 9 -> 15 -> 20 -> null");
    list = list_orderedAppend(&list, compare_int, &v1);
    TEST_LIST(list, "1 -> 4 -> 9 -> 15 -> 20 -> null");
    list = list_orderedAppend(&list, compare_int, &v9);    
    TEST_LIST(list, "1 -> 4 -> 9 -> 15 -> 20 -> null");
    list_destroy(list);
}

static void test_get_set_data(void) {
    int a = 1, b = 2;
    s_node *list = list_append(list_create(), &a);
    nb_tests++;
    if (list_get_data(list) != &a) nb_echecs++;
    list_set_data(list, &b);
    nb_tests++;
    if (list_get_data(list) != &b) nb_echecs++;
    list_destroy(list);
}



int main(void){
    test_liste_create();
    test_insert();
    test_append();
    test_remove();
    test_head_remove();
    test_ordered_append();
    test_get_set_data();

    printf("%d test(s), %d echec(s)\n", nb_tests, nb_echecs);
    return nb_echecs != 0;     
}