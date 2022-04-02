#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdbool.h>
#include "util.h"
#include "worker.h"



Worker* min_element(Worker* begin, Worker* end, _Bool (*less)(Worker*, Worker*));

void selection_sort(Worker* begin, Worker* end, _Bool (*less)(Worker*, Worker*));



#endif