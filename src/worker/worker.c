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