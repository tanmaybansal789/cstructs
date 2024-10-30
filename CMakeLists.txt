cmake_minimum_required(VERSION 3.28)
project(cstructs C)

set(CMAKE_C_STANDARD 99)

# asan
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

include_directories(include)
include_directories(tests)
include_directories(external/minunit)

set(CSTRUCTS_HEADERS
        include/cstructs_types.h
        include/cstructs_defines.h

        include/stack/stack.h
        include/queue/queue.h
        include/deque/deque.h
        include/darray/darray.h
)

set(CSTRUCTS_SOURCES
        src/stack/stack.c
        src/queue/queue.c
        src/deque/deque.c
        src/darray/darray.c
)

set(CSTRUCTS_TEST
        external/minunit/minunit.h

        tests/darray/darray_test.h
        tests/deque/deque_test.h
        tests/queue/queue_test.h
        tests/stack/stack_test.h
)

# tests
# add_executable(cstructs src/main.c
#        ${CSTRUCTS_HEADERS}
#        ${CSTRUCTS_SOURCES}
#        ${CSTRUCTS_TEST}
# )

# library
add_library(cstructs
        ${CSTRUCTS_HEADERS}
        ${CSTRUCTS_SOURCES}
)