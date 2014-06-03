#include <omp.h>
#include <stdio.h>
#include <time.h>
#include "qsort_p.h"


static int comp_int(const void* a, const void* b)
{
    int aa = *(int*) a;
    int bb = *(int*) b;

    if (aa < bb) return 1;
    if (aa > bb) return -1;
    return 0;
}


double benchmark(size_t size)
{
    int *array, i;
    double t1, t2;

    /* allocate */
    array = malloc(size * sizeof *array);
    if (array == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }

    /* fill */
    srand(time(NULL));
    for (i = 0; i < size; ++i) {
        array[i] = rand();
    }

    /* sort */
    t1 = omp_get_wtime();
    qsort_p(array, size, sizeof *array, comp_int);
    t2 = omp_get_wtime();

    free(array);

    return t2 - t1;
}


int main(void)
{
    int size = 4096;
    double elapsed_time = 0.0;

    printf("Number of threads: %d\n", omp_get_max_threads());
    printf("array size | elapsed time [ms]\n");
    while (elapsed_time < 60) {
        elapsed_time = benchmark(size);
        printf("%10i | %10.3f\n", size, elapsed_time * 1000);

        size *= 2;
    }

    return EXIT_SUCCESS;
}
