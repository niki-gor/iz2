#include "algo.h"
#include <assert.h>



void swap(Worker* a, Worker* b);

size_t min(size_t a, size_t b);

Worker* find_not_eq(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*)) {
    Worker* result;
    for (result = begin; result < end && eq(result, begin); ++result)
        ;
    return result;
}

// n -- кол-во отображаемых в ответе человек на одну должность
void group(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*), size_t n) {
    Worker* r;
    for (Worker* l = begin; l < end; l = r) {
        r = find_not_eq(l, end, eq);
        if ((size_t)(r - l) > n) {
            for (size_t i = 0; i < n / 2; ++i) {
                // (n+1)/2 -- кол-во первых (самых молодых) в ответе (напр. для n=5 будет 3, для n=4 будет 2)
                // n/2       -- кол-во последних (самых старых) в ответе (напр. для n=5 будет 2, для n=4 будет 2)
                // последние n/2 идут сразу же за первыми (n+1)/2
                *(l+(n+1)/2 + i) = *(r-1 - i);
            }
        }
    }
}

void sort_groups(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*), size_t n, _Bool (*less)(Worker*, Worker*)) {
    Worker* r;
    for (Worker* l = begin; l < end; l = r) {
        r = find_not_eq(l, end, eq);
        selection_sort(l, l + min(r - l, n), less);
    }
}

void print_groups(FILE* out, Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*), size_t n) {
    Worker* next;
    for (Worker* l = begin; l < end; l = next) {
        next = find_not_eq(l, end, eq);
        Worker* r = l + min(next - l, n);
        fprintf(out, "[POSITION: %s]\n", l->position);
        while (l < r) {
            print_worker(out, l++);
        }
        fprintf(out, "\n\n");
    }
}

void print_worker(FILE* out, Worker* w) {
    // выводится только основная информация о работнике, касающаяся запроса
    fprintf(out, "%s %s %d\n", w->position, w->surname, w->age);
}

void input_workers(FILE* in, Worker* begin, Worker* end) {
    for (Worker* it = begin; it < end; ++it) {
        input_worker(in, it);
    }
}

void input_worker(FILE* in, Worker* w) {
    // вводится только основная информация о работнике, касающаяся запроса
    fscanf(in, "%ms", &w->position);
    fscanf(in, "%ms", &w->surname);
    fscanf(in, "%d", &w->age);
}

void free_worker(Worker* w) {
    if (!w) {
        return;
    }
    if (w->position) {
        free(w->position);
    }
    if (w->surname) {
        free(w->surname);
    }
    if (w->name) {
        free(w->name);
    }
}

void free_workers(Worker* begin, Worker* end) {
    for (Worker* i = begin; i < end; ++i) {
        free_worker(i);
    }
    free(begin);
}