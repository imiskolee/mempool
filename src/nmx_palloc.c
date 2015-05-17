#include "nmx_palloc.h"


size_t nmx_pagesize = 0;

//#define nmx_MAX_ALLOC_FROM_POOL  (nmx_pagesize - 1)

#define NMX_MAX_ALLOC_FROM_POOL (nmx_pagesize == 0 ? (nmx_pagesize = getpagesize() -1) : (nmx_pagesize))

#define NMX_POOL_ALIGNMENT       16


static void *nmx_palloc_block(nmx_pool_t *pool, size_t size);
static void *nmx_palloc_large(nmx_pool_t *pool, size_t size);


nmx_pool_t *
nmx_create_pool(size_t size)
{
    nmx_pool_t  *p;

    p = nmx_memalign(NMX_POOL_ALIGNMENT, size);
    if (p == NULL) {
        return NULL;
    }

    p->d.last = (unsigned char *) p + sizeof(nmx_pool_t);
    p->d.end = (unsigned char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(nmx_pool_t);
    p->max = (size < NMX_MAX_ALLOC_FROM_POOL) ? size : NMX_MAX_ALLOC_FROM_POOL;

    p->current = p;
    p->large = NULL;

    return p;
}


void
nmx_destroy_pool(nmx_pool_t *pool)
{
    nmx_pool_t          *p, *n;
    nmx_pool_large_t    *l;

    for (l = pool->large; l; l = l->next) {

        if (l->alloc) {
            nmx_free(l->alloc);
        }
    }

    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        nmx_free(p);

        if (n == NULL) {
            break;
        }
    }
}


void
nmx_reset_pool(nmx_pool_t *pool)
{
    nmx_pool_t        *p;
    nmx_pool_large_t  *l;

    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            nmx_free(l->alloc);
        }
    }

    for (p = pool; p; p = p->d.next) {
        p->d.last = (unsigned char *) p + sizeof(nmx_pool_t);
        p->d.failed = 0;
    }

    pool->current = pool;
    pool->large = NULL;
}


void *
nmx_palloc(nmx_pool_t *pool, size_t size)
{
    unsigned char      *m;
    nmx_pool_t  *p;

    if (size <= pool->max) {

        p = pool->current;

        do {
            m = nmx_align_ptr(p->d.last, NMX_POOL_ALIGNMENT);

            if ((size_t) (p->d.end - m) >= size) {
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;

        } while (p);

        return nmx_palloc_block(pool, size);
    }



    return nmx_palloc_large(pool, size);
}


void *
nmx_pnalloc(nmx_pool_t *pool, size_t size)
{
    unsigned char      *m;
    nmx_pool_t  *p;


    if (size <= pool->max) {

        p = pool->current;

        do {
            m = p->d.last;

            if ((size_t) (p->d.end - m) >= size) {
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;

        } while (p);

        return nmx_palloc_block(pool, size);
    }


    return nmx_palloc_large(pool, size);
}


static void *
nmx_palloc_block(nmx_pool_t *pool, size_t size)
{
    unsigned char      *m;
    size_t       psize;
    nmx_pool_t  *p, *new;

    psize = (size_t) (pool->d.end - (unsigned char *) pool);

    m = nmx_memalign(NMX_POOL_ALIGNMENT, psize);
    if (m == NULL) {
        return NULL;
    }

    new = (nmx_pool_t *) m;

    new->d.end = m + psize;
    new->d.next = NULL;
    new->d.failed = 0;

    m += sizeof(nmx_pool_data_t);
    m = nmx_align_ptr(m, NMX_POOL_ALIGNMENT);
    new->d.last = m + size;

    for (p = pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            pool->current = p->d.next;
        }
    }

    p->d.next = new;

    return m;
}


static void *
nmx_palloc_large(nmx_pool_t *pool,size_t size)
{
    void              *p;
    int              n;
    nmx_pool_large_t  *large;

    p = nmx_alloc(size);
    if (p == NULL) {
        return NULL;
    }

    n = 0;

    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            large->alloc = p;
            return p;
        }

        if (n++ > 3) {
            break;
        }
    }

    large = nmx_palloc(pool, sizeof(nmx_pool_large_t));
    if (large == NULL) {
        nmx_free(p);
        return NULL;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}


void *
nmx_pmemalign(nmx_pool_t *pool, size_t size, size_t alignment)
{
    void              *p;
    nmx_pool_large_t  *large;

    p = nmx_memalign(alignment, size);
    if (p == NULL) {
        return NULL;
    }

    large = nmx_palloc(pool, sizeof(nmx_pool_large_t));
    if (large == NULL) {
        nmx_free(p);
        return NULL;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}


int
nmx_pfree(nmx_pool_t *pool, void *p)
{
    nmx_pool_large_t  *l;

    for (l = pool->large; l; l = l->next) {
        if (p == l->alloc) {

            nmx_free(l->alloc);
            l->alloc = NULL;

            return 1;
        }
    }

    return 0;
}

void *
nmx_pcalloc(nmx_pool_t *pool, size_t size)
{
    void *p;

    p = nmx_palloc(pool, size);
    if (p) {
        memset(p, 0,size);
    }

    return p;
}
