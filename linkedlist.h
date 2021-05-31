#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdint.h>

#define LL_MALLOCFAIL (2)
#define LL_ERROR      (1)
#define LL_OK         (0)

typedef unsigned int uint;

typedef struct ll_buffer {
    void*    data;
    size_t   len;
} ll_buffer;

typedef struct ll_node {
    ll_buffer        buf;
    struct ll_node*  next;
    struct ll_node*  prev;
} ll_node;

typedef struct ll_list {
    ll_node* head;
} ll_list;

typedef enum ll_print_mode {
    LL_DATA,
    LL_NODATA,
    LL_REVERSE
} ll_print_mode;

// Allocate empty list
ll_list* ll_create_empty();

// Append 
void ll_add_first(ll_list* list, void* data, size_t size);
void ll_add_last(ll_list* list, void* data, size_t size);
void ll_insert(ll_list* list, void* data, size_t size, uint index);

// Replace
void ll_replace_first(ll_list* list, void* data, size_t size);
void ll_replace_last(ll_list* list, void* data, size_t size);
void ll_replace_at(ll_list* list, void* data, size_t size, uint index);

// Remove
void ll_remove_first(ll_list* list);
void ll_remove_last(ll_list* list);
void ll_remove_at(ll_list* list, uint index);

// Clear entire list
void ll_clear(ll_list* list);

// Get 
ll_node* ll_peek_first(ll_list* list);
ll_node* ll_peek_last(ll_list* list);
ll_node* ll_peek_at(ll_list* list, uint index);

// Get and delete 
ll_node* ll_poll_first(ll_list* list);
ll_node* ll_poll_last(ll_list* list);
ll_node* ll_poll_at(ll_list* list, uint index);

// Get size 
uint ll_size(ll_list* list);

void ll_print(ll_list* list, ll_print_mode mode);

#endif