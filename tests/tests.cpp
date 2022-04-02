#include <gtest/gtest.h>

extern "C" {
    #include "algo.h"
    #include "worker.h"
    #include "sort.h"
    #include "util.h"
};



TEST (INPUT, TEST_INPUT) {
    char query[] = "    proger   ivanov  1337  ";
    FILE* in = fmemopen(query, sizeof(query), "r");

    Worker w;
    init_worker(&w);
    input_worker(in, &w);

    EXPECT_EQ(w.position, "proger");
    EXPECT_EQ(w.surname, "ivanov");
    EXPECT_EQ(w.age, 1337);

    free_worker(&w);
    fclose(in);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}