#include "algo.h"



int min_element_index(void* arg) {
    min_element_index_thr_arg* this = (min_element_index_thr_arg*)arg;
    _Bool done = false;
    size_t result = atomic_load(this->acnt);
    while (!done) {
        size_t i = atomic_fetch_add(this->acnt, 1);
        if (i < this->n) {
            if (this->less(&this->buffer[i], &this->buffer[result])) {
                result = i;
            }
        }
        else {
            done = true;
        }
    }

    int errflag = mtx_lock(&this->min_index->mtx);
    if (errflag != thrd_success) {
        /* Handle error */
    }
    if (this->less(&this->buffer[result], &this->buffer[this->min_index->val])) {
        this->min_index->val = result;
    }
    errflag = mtx_unlock(&this->min_index->mtx);
    if (errflag != thrd_success) {
        /* Handle error */
    }

    return 0;
}

void selection_sort(Worker* begin, Worker* end, _Bool (*less)(Worker*, Worker*)) {
    size_t cores = sysconf(_SC_NPROCESSORS_ONLN);
    thrd_t* threads = malloc(cores * sizeof(thrd_t));

    for (Worker* it = begin; it < end; ++it) {
        atomic_size_t acnt;
        atomic_store(&acnt, 0);
        protected_t min_index;
        min_index.val = 0;
        mtx_init(&min_index.mtx, mtx_plain);
        min_element_index_thr_arg arg = {.buffer = it, .n = end - it, .less = less, .acnt = &acnt, .min_index = &min_index};

        size_t use_now = min(end - it, cores);
        for (size_t thrd_cnt = 0; thrd_cnt < use_now; ++thrd_cnt) {
            int errflag = thrd_create(threads + thrd_cnt, min_element_index, &arg);
            if (errflag != thrd_success) {
                /* Handle error */
            }
        }
        for (size_t thrd_cnt = 0; thrd_cnt < use_now; ++thrd_cnt) {
            int errflag = thrd_join(threads[thrd_cnt], NULL);
            if (errflag != thrd_success) {
                /* Handle error */
            }
        }

        swap(it, &begin[min_index.val]);
    }

    free(threads);
}

void swap(Worker* a, Worker* b) {
    Worker tmp = *a;
    *a = *b;
    *b = tmp;
}

size_t min(size_t a, size_t b) {
    return (a < b ? a : b);
}

Worker* find_not_eq(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*)) {
    Worker* result;
    for (result = begin; result < end && eq(result, begin); ++result)
        ;
    return result;
}

void group(Worker* begin, Worker* end, _Bool (*eq)(Worker*, Worker*), size_t n) {
    Worker* r;
    for (Worker* l = begin; l < end; l = r) {
        r = find_not_eq(l, end, eq);
        if ((size_t)(r - l) > n) {
            for (size_t i = 0; i < n / 2; ++i) {
                *(l + (n + 1) / 2 + i) = *(r - 1 - i);
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
    Worker* r;
    for (Worker* l = begin; l < end; l = r) {
        r = find_not_eq(l, end, eq);
        for (size_t i = 0; i < min(r - l, n); ++i) {
            print_worker(out, begin + i);
        }
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

void input_string(FILE* in, char* s) {
    s = (char*)malloc(sizeof(char));
    size_t len = 0;
    size_t capacity = 0;

    char c;
    for (fscanf(in, "%c", &c); !isspace(c); fscanf(in, "%c", &c)) {
        if (len == capacity) {
            capacity = 1 + capacity * 3 / 2;
            s = (char*)realloc(s, capacity * sizeof(char));
        }
        s[len++] = c;
    }

    s = (char*)realloc(s, len + 1);
    s[len] = '\0';
}

void input_worker(FILE* in, Worker* w) {
    // вводится только основная информация о работнике, касающаяся запроса
    input_string(in, w->surname);
    input_string(in, w->position);
    fscanf(in, "%d", &w->age);
}