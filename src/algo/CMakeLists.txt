add_library(algo algo.h algo.c)
target_include_directories(algo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(algo LINK_PUBLIC worker)