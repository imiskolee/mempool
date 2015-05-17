#ifndef __nmx_alloc_H_
#define __nmx_alloc_H_
#include <stdlib.h>
void *nmx_alloc(size_t size);
void *nmx_calloc(size_t size);
void *nmx_realloc(void *p, size_t size);

#define nmx_free          free

#define nmx_align_ptr(p, a)                                                   \
    (unsigned char *) (((unsigned int ) (p) + ((unsigned int ) a - 1)) & ~((unsigned int ) a - 1))

void *nmx_memalign(size_t alignment, size_t size);

#endif //nmx_alloc_H_
