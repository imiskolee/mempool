#include "nmx_alloc.h"

void *
nmx_alloc(size_t size)
{
    void  *p;

    p = malloc(size);

    return p;
}


void *
nmx_calloc(size_t size)
{
    void  *p;

    p = nmx_alloc(size);

    if (p) {
        memset(p,0,size);
    }

    return p;
}

void *nmx_realloc(void *p, size_t size){

    if(p) {
        return realloc (p, size);
    }

    return NULL;

}

void *
        nmx_memalign(size_t alignment, size_t size)
{
    void  *p;
    int    err;

    err = posix_memalign(&p, alignment, size);

    return p;
}
