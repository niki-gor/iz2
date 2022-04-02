#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <threads.h>
#include <stdatomic.h>
#include "worker.h"
#include "util.h"



typedef struct {
    mtx_t mtx;
    size_t val;
} protected_t;

typedef struct {
    Worker* buffer;
    size_t n;
    _Bool (*less)(Worker*, Worker*);

    atomic_size_t* acnt;
    protected_t* min_index;
} min_element_index_thr_arg;

int min_element_index(void* arg);

void selection_sort(Worker* begin, Worker* end, _Bool (*less)(Worker*, Worker*));



#endif