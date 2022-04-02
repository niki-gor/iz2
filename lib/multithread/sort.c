#include "sort.h"



int min_element_index(void* arg) {
    min_element_index_thr_arg* this = (min_element_index_thr_arg*)arg;
    _Bool done = false;
    size_t result = 0;
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
        // Handle error
    }
    if (this->less(&this->buffer[result], &this->buffer[this->min_index->val])) {
        this->min_index->val = result;
    }
    errflag = mtx_unlock(&this->min_index->mtx);
    if (errflag != thrd_success) {
        // Handle error
    }

    return 0;
}

void selection_sort(Worker* begin, Worker* end, _Bool (*less)(Worker*, Worker*)) {
    size_t cores = sysconf(_SC_NPROCESSORS_ONLN);
    thrd_t* threads = malloc(cores * sizeof(thrd_t));

    for (; begin < end; ++begin) {
        atomic_size_t acnt;
        atomic_store(&acnt, 0);
        protected_t min_index;
        min_index.val = 0;
        mtx_init(&min_index.mtx, mtx_plain);
        min_element_index_thr_arg arg = {.buffer = begin, .n = end - begin, .less = less, .acnt = &acnt, .min_index = &min_index};

        size_t use_now = min(end - begin, cores);
        for (size_t thrd_cnt = 0; thrd_cnt < use_now; ++thrd_cnt) {
            int errflag = thrd_create(threads + thrd_cnt, min_element_index, &arg);
            if (errflag != thrd_success) {
                // Handle error
            }
        }
        for (size_t thrd_cnt = 0; thrd_cnt < use_now; ++thrd_cnt) {
            int errflag = thrd_join(threads[thrd_cnt], NULL);
            if (errflag != thrd_success) {
                // Handle error
            }
        }

        swap(begin, &begin[min_index.val]);
    }

    free(threads);
}