#include <stdio.h>
#include <stdlib.h>
#include "qsort_p.h"


static int comp_int(const void* a, const void* b)
{
    int aa = *(int*) a;
    int bb = *(int*) b;

    if (aa > bb) return 1;
    if (aa < bb) return -1;
    return 0;
}


int main(void)
{
    const size_t size = 100000;
    int *array, *sorted, i, has_error;

    array = malloc(size * sizeof *array);
    sorted = malloc(size * sizeof *sorted);
    if (array == NULL || sorted == NULL) {
        fprintf(stderr, "not ok - malloc error\n");
        return EXIT_FAILURE;
    }

    srand(0);
    for (i = 0; i < size; ++i) {
        array[i] = rand();
    }
    memcpy(sorted, array, size * sizeof *array);

    qsort_p(sorted, size, sizeof *sorted, comp_int);

#ifdef DEBUG
    printf("Before      After\n");
    for (i = 0; i < size; ++i) {
        printf("%10d  %10d\n", array[i], sorted[i]);
    }
#endif

    has_error = 0;
    for (i = 0; i < size - 1; ++i) {
        if (sorted[i] > sorted[i+1]) {
            ++has_error;
#ifdef DEBUG
            printf("[%d] %d > [%d] %d\n", i, sorted[i], i+1, sorted[i+1]);
#endif
        }
    }
    if (has_error) {
        printf("not ok - wrong result\n");
    } else {
        printf("ok\n");
    }

    free(array);
    free(sorted);

    return has_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
