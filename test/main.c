#include <stdlib.h>
#include <stdio.h>
#include "../src/mempool.h"

int main(){

   ngx_pool_t *pool = ngx_create_pool(1024);

   char *p = (char *)ngx_pcalloc (pool,1024 * 1024 *128);
   char *d = (char *)ngx_pcalloc (pool,1024 * 1024 * 128);

    sleep(5);

    ngx_destroy_pool (pool);

    sleep(5);
}
