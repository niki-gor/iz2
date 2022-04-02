#include <stdio.h>
#include "worker.h"
#include "algo.h"



int main() {
    const size_t workers_per_position = 3;

    char query[] = "8   d  surname 18   \
     a surname 30   \
      c z 122     c x 20        c unused1 40  \
     c unused2 40  c unused3 40  c y 15";

    FILE* in = fmemopen(query, sizeof(query), "r");

    size_t n;
    fscanf(in, "%zu", &n);
    Worker* workers = (Worker*)malloc(n * sizeof(Worker));
    init_workers(workers, workers + n);

    input_workers(in, workers, workers + n);

    selection_sort(workers, workers + n, compare_position_and_age);

    group(workers, workers + n, eq_position, workers_per_position);

    sort_groups(workers, workers + n, eq_position, workers_per_position, compare_surname);

    print_groups(stdout, workers, workers + n, eq_position, workers_per_position);

    free_workers(workers, workers + n);

    fclose(in);

    return 0;
}