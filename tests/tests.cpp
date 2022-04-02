#include <gtest/gtest.h>

extern "C" {
    #include "algo.h"
    #include "worker.h"
};



TEST (INPUT, TEST_INPUT) {
    char helloworld[] = "    Hello ,    world     ";
    FILE* in = fmemopen(helloworld, strlen(helloworld), "r");

    char* hello;
    input_string(in, hello);
    char* comma;
    input_string(in, comma);
    char* world;
    input_string(in, world);

    EXPECT_EQ(hello, "Hello");
    EXPECT_EQ(comma, ",");
    EXPECT_EQ(world, "world");

    free(hello);
    free(comma);
    free(world);  
}