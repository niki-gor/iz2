#include "worker.h"



_Bool compare_position_and_age(Worker* l, Worker* r) {
    int cmp = strcmp(l->position, r->position);
    return (cmp == 0 ? l->age < r->age : cmp < 0);
}

_Bool compare_surname(Worker* l, Worker* r) {
    return strcmp(l->surname, r->surname) < 0;
}

_Bool eq_position(Worker* a, Worker* b) {
    return !strcmp(a->position, b->position);
}

void init_worker(Worker* w) {
    w->name = w->surname = w->position = NULL;
}

void init_workers(Worker* begin, Worker* end) {
    for (; begin < end; ++begin) {
        init_worker(begin);
    }
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