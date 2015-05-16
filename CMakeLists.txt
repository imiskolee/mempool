project(m_mempool)

AUX_SOURCE_DIRECTORY(./src/ SRCS)

set(HEADER_LIST ./src/nmx_alloc.h ./src/nmx_palloc.h)

ADD_LIBRARY(m_mempool SHARED ${SRCS})
install(TARGETS m_mempool DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include/nmx_mempool)


