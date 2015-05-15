#include "ngx_alloc.h"

void *
ngx_alloc(size_t size)
{
    void  *p;

    p = malloc(size);

    return p;
}


void *
ngx_calloc(size_t size)
{
    void  *p;

    p = ngx_alloc(size);

    if (p) {
        memset(p,0,size);
    }

    return p;
}

void *
        ngx_memalign(size_t alignment, size_t size)
{
    void  *p;
    int    err;

    err = posix_memalign(&p, alignment, size);

    return p;
}
