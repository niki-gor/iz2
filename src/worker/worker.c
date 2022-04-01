#include "worker.h"



_Bool compare_position_and_age(Worker* l, Worker* r) {
    if (strcmp(l->position, r->position) < 0) {
        return true;
    }
    else {
        return l->age < r->age;
    }
}

_Bool compare_surname(Worker* l, Worker* r) {
    return strcmp(l->surname, r->surname) < 0;
}

_Bool eq_position(Worker* a, Worker* b) {
    return !strcmp(a->position, b->position);
}