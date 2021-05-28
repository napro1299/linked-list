#include <stdio.h>

#include "linkedlist.h"

#define LL_INIT(name) \
    struct ll_node_t name; \
    ll_create_empty(&name) 

#define LL_BACKWARD_LINK(tolink, linked) \
    (tolink)->next = (struct ll_node_t*)linked; \
    if ((linked)->prev) { \
        (linked)->prev->next = (struct ll_node_t*)tolink; \
        (tolink)->prev = (struct ll_node_t*)(linked)->prev; } \
    (linked)->prev = (struct ll_node_t*)tolink

#define LL_FORWARD_LINK(tolink, linked) \
    (tolink)->prev = (ll_node_t*)linked; \
    if ((linked)->next) { \
        (linked)->next->prev = (ll_node_t*)tolink; \
        (tolink)->next = (ll_node_t*)(linked)->next; } \
    (linked)->next = (ll_node_t*)tolink

#define EMPTY_NODE(node) \
    node->buf.data = NULL; \
    node->buf.len = 0; \
    node->next = NULL; \
    node->prev = NULL 

int ll_create_empty(struct ll_node_t* node) {
    if (node->next || node->prev)
        return LL_ERROR;
    EMPTY_NODE(node);
    return LL_OK;
}

struct ll_node_t* ll_add_first(struct ll_node_t* head, void* data, size_t size) {
    LL_INIT(new_head);
    new_head.buf.data = data;
    new_head.buf.len = size;
    LL_BACKWARD_LINK(&new_head, head);
    return &new_head;
}

int main(int argc, char** argv) {

    char some_data[] = "dF5ja4EjHu8dsDE8Dwe2f3j\n";
    char other_data[] = "other data\n";

    struct ll_node_t lkd_list;
    int result = ll_create_empty(&lkd_list);

    if (result != LL_OK) {
        printf("tried to empty linked node.\n");
        goto end;
    }

    lkd_list.buf.data = other_data;
    lkd_list.buf.len = 12;

    struct ll_node_t* ll = ll_add_first(&lkd_list, some_data, 25);

    printf("head: %s", lkd_list.buf.data);
    printf("next: %s", ll->buf.data);

    end: getchar();
}