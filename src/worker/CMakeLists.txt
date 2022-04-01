add_library(worker worker.h worker.c)
target_include_directories(worker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})