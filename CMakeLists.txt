cmake_minimum_required(VERSION 3.0.0)

project(db C CXX)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage ")
set(CMAKE_C_FLAGS "-pthread --coverage")
add_executable(${PROJECT_NAME} main.c)

add_subdirectory(src)
# add_subdirectory(tests)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC algo worker)