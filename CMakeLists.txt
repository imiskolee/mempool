project(nmx_mempool)
SET(CMAKE_C_FLAGS_DEBUG  "-std=c99 -Wall -O0 -Wall -g -ggdb")
SET(CMAKE_C_FLAGS_RELEASE "-std=c99 -Wall -Wno-unused-variable -Wunused-function -Wunused-label -Wuninitialized -O3 -Wall")

AUX_SOURCE_DIRECTORY(./src/ SRCS)

set(HEADER_LIST ./src/nmx_alloc.h ./src/nmx_palloc.h)

ADD_LIBRARY(nmx_mempool SHARED ${SRCS})
install(TARGETS nmx_mempool DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include/nmx_mempool)


