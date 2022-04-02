#ifndef WORKER_H
#define WORKER_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct Experience {
    int years;
    int months;
    int days;
} Experience;

typedef enum {
    M, F
} Gender;

typedef struct Worker {
    char* name;             // 0 + 8 = 8    (кратно 8)
    char* surname;          // 8 + 8 = 16   (кратно 16)
    char* position;         // 16 + 8 = 24  (кратно 8)
    int age;                // 24 + 4 = 28  (кратно 4)
    int salary;             // 28 + 4 = 32  (кратно 32)
    Experience experience;  // 32 + 12 = 44 (кратно 4)
    Gender gender;          // 44 + 1 = 45
} Worker;                   // занято 48 байт (если располагать поля как описано в задании, то будет 56)

_Bool compare_position_and_age(Worker* l, Worker* r);

_Bool compare_surname(Worker* l, Worker* r);

_Bool eq_position(Worker* a, Worker* b);

void init_worker(Worker* w);
void init_workers(Worker* begin, Worker* end);

void free_worker(Worker* w);
void free_workers(Worker* begin, Worker* end);



#endif