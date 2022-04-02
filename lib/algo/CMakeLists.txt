set(THIS_LIB_NAME algo)

add_library(${THIS_LIB_NAME} ${THIS_LIB_NAME}.c)
target_include_directories(${THIS_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${THIS_LIB_NAME} LINK_PUBLIC worker util)