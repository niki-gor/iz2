cmake_minimum_required(VERSION 3.14)
project(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE algo worker sort util GTest::GTest GTest::Main)