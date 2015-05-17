#ifndef __nmx_palloc_H_
#define __nmx_palloc_H_

#include <stdlib.h>

#include "nmx_alloc.h"

typedef struct nmx_pool_large_s nmx_pool_large_t;

typedef struct nmx_pool_s nmx_pool_t;

struct nmx_pool_large_s {
    nmx_pool_large_t *next;
    void *alloc;
};

typedef struct {
    unsigned char *last;
    unsigned char *end;
    nmx_pool_t *next;
    unsigned int failed;
} nmx_pool_data_t;

struct nmx_pool_s {

    nmx_pool_data_t d;
    size_t max;
    nmx_pool_t *current;
    nmx_pool_large_t *large;
};


/*  ======================================
 *  ++++++++  Library Open API  ++++++++++
 *  ======================================
 */


void *nmx_alloc (size_t size);

void *nmx_calloc (size_t size);

nmx_pool_t *nmx_create_pool (size_t size);

void nmx_destroy_pool (nmx_pool_t *pool);

void nmx_reset_pool (nmx_pool_t *pool);

void *nmx_palloc (nmx_pool_t *pool, size_t size);

void *nmx_pnalloc (nmx_pool_t *pool, size_t size);

void *nmx_prealloc (nmx_pool_t *pool, void *p, size_t size);

void *nmx_pcalloc (nmx_pool_t *pool, size_t size);

void *nmx_pmemalign (nmx_pool_t *pool, size_t size, size_t alignment);

int nmx_pfree (nmx_pool_t *pool, void *p);


#endif //nmx_palloc.h_H_
