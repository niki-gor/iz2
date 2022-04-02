#ifndef ALGO_H
#define ALGO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "worker.h"
#include "util.h"
#include "sort.h"



Worker* find_not_eq(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*));

void group(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*), size_t n);

void sort_groups(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*), size_t n, _Bool (*less)(Worker*, Worker*));

void print_groups(FILE* out, Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*), size_t n);

void print_worker(FILE* out, Worker* w);

void input_worker(FILE* in, Worker* w);

void input_workers(FILE* in, Worker* begin, Worker* end);

void input_string(FILE* in, char* s);



#endif