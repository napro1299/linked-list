#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdint.h>

#define LL_ERROR (-1)
#define LL_OK    (0)

struct ll_buffer_t {
    void*    data;
    uint32_t len;
};

struct ll_node_t {
    struct ll_buffer_t buf;
    struct ll_node_t*  next;
    struct ll_node_t*  prev;
};

enum ll_print_mode {
    DATA,
    NODATA
};

int ll_create_empty(struct ll_node_t* node);

struct ll_node_t* ll_add_first(struct ll_node_t* head, void* data, size_t size);
void ll_add_last(struct ll_node_t* head, void* data, size_t size);
struct ll_node_t* ll_insert(struct ll_node_t* head, void* data, size_t size, uint32_t index);

void ll_replace_first(struct ll_node_t* head, void* data, size_t size);
void ll_replace_last(struct ll_node_t* head, void* data, size_t);
void ll_replace_at(struct ll_node_t* head, void* data, size_t size, uint32_t index);

struct ll_node_t* ll_remove_first(struct ll_node_t* head);
void ll_remove_last(struct ll_node_t* head);
struct ll_node_t* ll_remove_at(struct ll_node_t* head, uint32_t index);

void ll_clear(struct ll_node_t* head);

struct ll_node_t* ll_peek_first(struct ll_node_t* head);
struct ll_node_t* ll_peek_last(struct ll_node_t* head);
struct ll_node_t* ll_peek_at(struct ll_node_t* head, uint32_t index);

struct ll_node_t* ll_poll_first(struct ll_node_t* head);
struct ll_node_t* ll_poll_last(struct ll_node_t* head);
struct ll_node_t* ll_poll_at(struct ll_node_t* head);

int ll_size(struct ll_node_t* head);

void ll_print(struct ll_node_t head, enum ll_print_mode mode);

#endif