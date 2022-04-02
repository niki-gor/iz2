#include "util.h"



void swap(Worker* a, Worker* b) {
    Worker tmp = *a;
    *a = *b;
    *b = tmp;
}

size_t min(size_t a, size_t b) {
    return (a < b ? a : b);
}