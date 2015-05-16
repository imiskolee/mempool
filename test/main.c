#include <stdlib.h>
#include <unistd.h>
#include "../src/nmx_palloc.h"

int main(){

   nmx_pool_t *pool = nmx_create_pool(1024);

    int i=0;

    for(i=0;i<10000;i++){

        nmx_pcalloc (pool,800 * 10);

    }

    sleep(5);

    nmx_destroy_pool (pool);

    sleep(5);
}
