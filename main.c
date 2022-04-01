#include <stdio.h>
#include "worker.h"
#include "algo.h"



int main() {
    const size_t workers_per_position = 3;

    size_t n;
    fscanf(stdin, "%zu", &n);
    Worker* workers = (Worker*)malloc(n * sizeof(Worker));

    input_workers(stdin, workers, workers + n);

    selection_sort(workers, workers + n, compare_position_and_age);

    group(workers, workers + n, eq_position, workers_per_position);

    sort_groups(workers, workers + n, eq_position, workers_per_position, compare_surname);

    print_groups(stdout, workers, workers + n, eq_position, workers_per_position);

    free(workers);
}