#include <omp.h>
#include <stdio.h>
#include <time.h>
#include "qsort_p.h"


static int comp_int(const void* a, const void* b)
{
    int aa = *(int*) a;
    int bb = *(int*) b;

    if (aa > bb) return 1;
    if (aa < bb) return -1;
    return 0;
}


double benchmark(size_t size, int is_parallel)
{
    int *array, i;
    double t1, t2;

    /* allocate */
    array = malloc(size * sizeof *array);
    if (array == NULL) {
        return -1.0;
    }

    /* fill */
    for (i = 0; i < size; ++i) {
        array[i] = rand();
    }

    /* sort */
    if (is_parallel) {
        t1 = omp_get_wtime();
        qsort_p(array, size, sizeof *array, comp_int);
        t2 = omp_get_wtime();
    } else {
        t1 = omp_get_wtime();
        qsort(array, size, sizeof *array, comp_int);
        t2 = omp_get_wtime();
    }

    free(array);

    return t2 - t1;
}


int main(int argc, char** argv)
{
    int num_iteration = 5;
    size_t size = 8192;
    double elapsed_time_s_average, elapsed_time_p_average;
    double *elapsed_time_s, *elapsed_time_p;

    if (argc == 2) {
        size = (size_t)atol(argv[1]);
    }

    elapsed_time_s = malloc(num_iteration * sizeof *elapsed_time_s);
    elapsed_time_p = malloc(num_iteration * sizeof *elapsed_time_p);

    printf("# Number of threads: %d\n", omp_get_max_threads());
    printf("# Number of iterations: %d\n", num_iteration);
    printf("# Array length   qsort [s]   qsort_p [s]   Speed up\n");

    while (1 /* will exit by malloc error */) {
        unsigned int random_seed = (unsigned int) time(NULL);
        int i;

        srand(random_seed); /* ensure same condition */
        for (i = 0; i < num_iteration; ++i) {
            elapsed_time_s[i] = benchmark(size, 0);
            if (elapsed_time_s[i] < 0) goto finish;
        }

        srand(random_seed); /* ensure same condition */
        for (i = 0; i < num_iteration; ++i) {
            elapsed_time_p[i] = benchmark(size, 1);
            if (elapsed_time_p[i] < 0) goto finish;
        }

        elapsed_time_s_average = 0.0;
        elapsed_time_p_average = 0.0;
        for (i = 0; i < num_iteration; ++i) {
            elapsed_time_s_average += elapsed_time_s[i];
            elapsed_time_p_average += elapsed_time_p[i];
        }
        elapsed_time_s_average /= num_iteration;
        elapsed_time_p_average /= num_iteration;

        printf("%14ld %11.6f   %11.6f %10.3f\n",
                (long)size, elapsed_time_s_average, elapsed_time_p_average,
                elapsed_time_s_average / elapsed_time_p_average);

        size *= 2;
    }

finish:

    free(elapsed_time_s);
    free(elapsed_time_p);

    return EXIT_SUCCESS;
}
