project(m_mempool)

AUX_SOURCE_DIRECTORY(./src/ SRCS)

ADD_LIBRARY(m_mempool ${SRCS})

add_executable(m_mempool ${SRCS} ./test/main.c)

