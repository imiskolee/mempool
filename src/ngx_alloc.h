#ifndef __ngx_alloc_H_
#define __ngx_alloc_H_
#include <stdlib.h>
void *ngx_alloc(size_t size);
void *ngx_calloc(size_t size);

#define ngx_free          free

#define ngx_align_ptr(p, a)                                                   \
    (u_char *) (((unsigned int ) (p) + ((unsigned int ) a - 1)) & ~((unsigned int ) a - 1))

void *ngx_memalign(size_t alignment, size_t size);

#endif //ngx_alloc_H_
