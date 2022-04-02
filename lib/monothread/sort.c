#include "sort.h"



Worker* min_element(Worker* begin, Worker* end, _Bool (*less)(Worker*, Worker*)) {
    Worker* result;
    for (result = begin; begin < end; ++begin) {
        if (less(begin, result)) {
            result = begin;
        }
    }
    return result;
}

void selection_sort(Worker* begin, Worker* end, _Bool (*less)(Worker*, Worker*)) {
    for (; begin < end; ++begin) {
        swap(begin, min_element(begin, end, less));
    }
}