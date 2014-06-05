#include <memory.h>
#include <omp.h>
#include "config.h"
#include "qsort_p.h"


static void swap(void* a, void* b, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i) {
        char temp;
        temp = ((char*)a)[i];
        ((char*)a)[i] = ((char*)b)[i];
        ((char*)b)[i] = temp;
    }
}


static void qsort_p_recursive(
        void* base,
        size_t num,
        size_t size,
        int (*compar)(const void*, const void*),
        size_t threshold)
{
    const int beg = 0;
    const int end = num - 1;
    void* comp;
    int piv, i, j;

    /* fast return */
    if (num < threshold) {
        if (num > 1) {
            qsort(base, num, size, compar);
        }
        return;
    }

    /* select a pivot (find median from seven points) */
    comp = malloc(7 * size);
    if (comp != NULL && threshold > 6) {
        const int m01 = beg + 1;
        const int m02 = num / 2 - 1;
        const int m03 = num / 2;
        const int m04 = num / 2 + 1;
        const int m05 = end - 1;

        memcpy((char*)comp + 0 * size, (char*)base + beg * size, size);
        memcpy((char*)comp + 1 * size, (char*)base + m01 * size, size);
        memcpy((char*)comp + 2 * size, (char*)base + m02 * size, size);
        memcpy((char*)comp + 3 * size, (char*)base + m03 * size, size);
        memcpy((char*)comp + 4 * size, (char*)base + m04 * size, size);
        memcpy((char*)comp + 5 * size, (char*)base + m05 * size, size);
        memcpy((char*)comp + 6 * size, (char*)base + end * size, size);
        qsort(comp, 7, size, compar);
        if (memcmp((char*)base + beg * size, (char*)comp + 3 * size, size) == 0) {
            piv = beg;
        } else if (memcmp((char*)base + m01 * size, (char*)comp + 3 * size, size) == 0) {
            piv = m01;
        } else if (memcmp((char*)base + m02 * size, (char*)comp + 3 * size, size) == 0) {
            piv = m02;
        } else if (memcmp((char*)base + m03 * size, (char*)comp + 3 * size, size) == 0) {
            piv = m03;
        } else if (memcmp((char*)base + m04 * size, (char*)comp + 3 * size, size) == 0) {
            piv = m04;
        } else if (memcmp((char*)base + m05 * size, (char*)comp + 3 * size, size) == 0) {
            piv = m05;
        } else {
            piv = end;
        }
    } else {
        piv = end;
    }
    free(comp);

    /* sort */
    i = beg;
    j = end;
    while (1) {
        while (i <= end && compar((char*)base + i * size, (char*)base + piv * size) < 0) {
            ++i;
        }
        while (j >= beg && compar((char*)base + j * size, (char*)base + piv * size) > 0) {
            --j;
        }

        if (i < j) {
            swap((char*)base + i * size, (char*)base + j * size, size);

            if (i == piv) {
                piv = j;
            } else if (j == piv) {
                piv = i;
            }

            ++i;
            --j;
        } else {
            piv = i == num ? j : i;
            break;
        }
    }

    /* recursion (we have to care about the number of threads) */
    if (piv > threshold && num - piv > threshold) {
        #pragma omp parallel sections
        {
            #pragma omp section
            qsort_p_recursive(base, piv, size, compar, threshold);
            #pragma omp section
            qsort_p_recursive((char*)base + piv * size, num - piv, size, compar, threshold);
        }
    } else {
        qsort(base, piv, size, compar);
        qsort((char*)base + piv * size, num - piv, size, compar);
    }
}


void qsort_p(void* base, size_t num, size_t size, int (*compar)(const void*, const void*))
{
    int threshold, nested_saved;

    threshold = num / omp_get_max_threads() / 10; /* heuristic parameter */
    if (threshold < 8192) {
        threshold = 8192;
    }

    nested_saved = omp_get_nested();
    omp_set_nested(1);

    qsort_p_recursive(base, num, size, compar, threshold);

    omp_set_nested(nested_saved);
}


void FC_FUNC(qsort_p, QSORT_P)(
        void* base,
        int* num,
        int* size,
        int (*compar)(const void*, const void*))
{
    qsort_p(base, (size_t)*num, (size_t)*size, compar);
}
