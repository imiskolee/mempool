#ifndef __ngx_palloc_H_
#define __ngx_palloc_H_
#include <stdlib.h>
#include "ngx_alloc.h"
typedef struct ngx_pool_large_s  ngx_pool_large_t;
typedef struct ngx_pool_s  ngx_pool_t;

struct ngx_pool_large_s {
    ngx_pool_large_t     *next;
    void                 *alloc;
};


typedef struct {
    u_char               *last;
    u_char               *end;
    ngx_pool_t           *next;
    unsigned int         failed;
} ngx_pool_data_t;

struct ngx_pool_s {

    ngx_pool_data_t       d;
    size_t                max;
    ngx_pool_t           *current;
    ngx_pool_large_t     *large;
};

void *ngx_alloc(size_t size);
void *ngx_calloc(size_t size);

ngx_pool_t *ngx_create_pool(size_t size);
void ngx_destroy_pool(ngx_pool_t *pool);
void ngx_reset_pool(ngx_pool_t *pool);

void *ngx_palloc(ngx_pool_t *pool, size_t size);
void *ngx_pnalloc(ngx_pool_t *pool, size_t size);
void *ngx_pcalloc(ngx_pool_t *pool, size_t size);
void *ngx_pmemalign(ngx_pool_t *pool, size_t size, size_t alignment);
int ngx_pfree(ngx_pool_t *pool, void *p);


#endif //ngx_palloc.h_H_
