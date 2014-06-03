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


int main(void)
{
    const size_t size = 10000;
    const size_t extract_size = 5;
    int *array, i;

    array = malloc(size * sizeof *array);
    if (array == NULL) {
        fprintf(stderr, "malloc error\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    for (i = 0; i < size; ++i) {
        array[i] = rand();
    }

    printf("Before sort: ");
    for (i = 0; i < extract_size; ++i) {
        printf("%d ", array[i]);
    }
    printf("... ");
    for (i = size - extract_size; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    qsort_p(array, size, sizeof *array, comp_int);

    printf("After sort: ");
    for (i = 0; i < extract_size; ++i) {
        printf("%d ", array[i]);
    }
    printf("... ");
    for (i = size - extract_size; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}
