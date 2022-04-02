
cmake_minimum_required(VERSION 3.0.0)

set(MULTITHREADING 1)

project(db C CXX)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage ")
set(CMAKE_C_FLAGS "-pthread -coverage")
add_executable(${PROJECT_NAME} main.c)

add_subdirectory(lib/worker)
add_subdirectory(lib/util)
add_subdirectory(lib/algo)
if (${MULTITHREADING})
    add_subdirectory(lib/multithread)
elseif (NOT ${MULTITHREADING})
    add_subdirectory(lib/monothread)
endif()

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC algo worker util sort)

if (${TESTS})
    add_subdirectory(tests)
endif()