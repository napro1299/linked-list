#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

#define LL_DEBUG
#ifdef LL_DEBUG
static void* ll_malloc(size_t size, int line, const char* file) {
    printf("MALLOC: file: %s line: %d\n", file, line);
    return malloc(size);
}

static void ll_free(void* ptr, int line, const char* file) {
    printf("FREE: file: %s line: %d\n", file, line);
    free(ptr);
}
#endif

#define malloc(m) ll_malloc(m, __LINE__, __FILE__)
#define free(m) ll_free(m, __LINE__, __FILE__)

#define HANG getchar()
#define d printf("Checkpoint."); HANG;

#define PRINT_DATA_MAX (10)

static ll_node* create_node() {
    ll_node* node = (ll_node*)malloc(sizeof(ll_node));
    node->next = NULL;
    node->prev = NULL;
    node->buf.data = NULL;
    node->buf.len = 0;
    return node;
}

ll_list* ll_create_empty() {
    ll_list* list = (ll_list*)malloc(sizeof(ll_list));
    list->head = create_node();
    return list;
}

void ll_add_first(ll_list* list, void* data, size_t size) {
    if (!list || !list->head) return;
    ll_node* new_head = create_node();
    new_head->buf.data = data;
    new_head->buf.len = size;
    new_head->next = list->head;
    list->head->prev = new_head;
    list->head = new_head;
}

void ll_add_last(ll_list* list, void* data, size_t size) {
    if (!list || !list->head) return;
    ll_node* cur;
    ll_node* new_node = create_node();
    new_node->buf.data = data;
    new_node->buf.len = size;
    for (cur = list->head; cur->next != NULL; cur = cur->next);
    cur->next = new_node;
    new_node->prev = cur;
}

// Inserts a node at a specified index in the list.
void ll_insert(ll_list* list, void* data, size_t size, uint index) {
    if (!list || !list->head) return;
    uint i;
    ll_node* cur;
    ll_node* new_node;
    for (cur = list->head, i = 0; i != index; cur = cur->next, i++) {
        if (cur->next == NULL) return; // reached end of list prematurely - index out of bounds
    }
    new_node = create_node();
    new_node->buf.data = data;
    new_node->buf.len = size;
    new_node->next = cur;
    if (cur->prev != NULL) {
        new_node->prev = cur->prev;
        cur->prev->next = new_node;
    } else {
        list->head = new_node;
    }
    cur->prev = new_node;
}

void ll_replace_first(ll_list* list, void* data, size_t size) {
    if (!list || !list->head) return;
    free(list->head->buf.data);
    list->head->buf.data = data;
    list->head->buf.len = size;
}

void ll_replace_last(ll_list* list, void* data, size_t size) {
    if (!list || !list->head) return;
    ll_node* cur;
    for (cur = list->head; cur->next; cur = cur->next);
    free(cur->buf.data);
    cur->buf.data = data;
    cur->buf.len = size;
}

void ll_replace_at(ll_list* list, void* data, size_t size, uint index) {
    if (!list || !list->head) return;
    uint i;
    ll_node* cur;
    for (cur = list->head, i = 0; i != index; cur = cur->next, i++) {
        if (!cur->next) return; // out of bounds
    }
    free(cur->buf.data);
    cur->buf.data = data;
    cur->buf.len = size;
}

void ll_remove_first(ll_list* list) {
    if (!list || !list->head) return;
    if (!list->head->next) {
        free(list->head->buf.data);
        free(list->head);
        list->head->buf.len = 0;
        return;
    }
    ll_node* next = list->head->next;

    free(list->head->buf.data);
    free(list->head);
    list->head->buf.len = 0;

    list->head = next;
}

void ll_remove_last(ll_list* list) {
    if (!list || !list->head) return;
    ll_node* cur;
    for (cur = list->head; cur->next; cur = cur->next);

    free(cur->buf.data);
    free(cur);
    cur->buf.len = 0;
}

void ll_remove_at(ll_list* list, uint index) {
    if (!list || !list->head) return;
    uint i;
    ll_node* cur;
    for (cur = list->head, i = 0; i != index; cur = cur->next, i++) {
        if (!cur->next) return; // out of bounds
    }
    if (cur->prev) {
        cur->prev = cur->next;
        cur->next->prev = cur->prev;
    } else {
        list->head = cur->next;
    }
    
    free(cur->buf.data);
    free(cur);
    cur->buf.len = 0;
}

void ll_print(ll_list* list, ll_print_mode mode) {
    if (!list || !list->head) return;
    switch (mode) {
        case LL_NODATA: {
            uint i;
            ll_node* cur;
            for (i = 0, cur = list->head; cur; cur = cur->next, ++i) { 
                if (i == 0)
                    printf("|\n+--head(%d)\n|\n", i++);
                else
                    printf("|\n+--node(%d)\n|\n", i);
            }
            break;
        }
        case LL_DATA: {
            uint i;
            ll_node* cur;
            for (i = 0, cur = list->head; cur; cur = cur->next, i++) { 
                if (i == 0)
                    printf("|\n+--head(%d) len: %d [%.*s]\n|\n", i, cur->buf.len, PRINT_DATA_MAX, cur->buf.data);
                else 
                    printf("|\n+--node(%d) len: %d [%.*s]\n|\n", i, cur->buf.len, PRINT_DATA_MAX, cur->buf.data);
            }
            break;
        }
        default: break;
    }
}

int main(int argc, char** argv) {
    char* node = "node";
    ll_list* list = ll_create_empty();
    for (int i = 0; i < 2; i++) ll_add_last(list, node, 4);

    char* replf = "replf";
    ll_replace_last(list, replf, 5);

    ll_print(list, LL_DATA);
    HANG;
}
