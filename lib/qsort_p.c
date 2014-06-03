#include <omp.h>
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
    const int mid = num / 2;
    const int end = num - 1;
    int comp1, comp2, comp3;
    int piv, i, j;

    /* fast return */
    if (num < 3) {
        if (num == 2) {
            if (compar(base, base + size) == -1) {
                swap(base, base + size, size);
            }
        }
        return;
    }

    /* select a pivot */
    comp1 = compar(base + beg * size, base + mid * size);
    comp2 = compar(base + mid * size, base + end * size);
    i = beg;
    j = end;

    if (comp1 == 0 || comp2 == 0 || comp1 + comp2 != 0) {
        /* c1 c2
         *  0  * : end <= mid = beg or beg = mid <= end
         *  *  0 : beg <= mid = end or end = mid <= beg
         *  1  1 : beg < mid < end
         * -1 -1 : end > mid > beg
         */
        piv = mid;
    } else {
        /* c1 c2 c3
         *  1 -1  1 : beg < end < mid
         *  1 -1  0 : beg = end < mid
         *  1 -1 -1 : end < beg < mid
         * -1  1  1 : mid < beg < end
         * -1  1  0 : mid < beg = end
         * -1  1 -1 : mid < end < beg
         */
        comp3 = compar(base + beg * size, base + end * size);
        piv = comp1 == comp3 ? end : beg;
    }

    /* sort */
    while (1) {
        while (i <= end && compar(base + i * size, base + piv * size) > 0) {
            ++i;
        }
        while (j >= beg && compar(base + j * size, base + piv * size) < 0) {
            --j;
        }

        if (i < j) {
            swap(base + i * size, base + j * size, size);

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
            qsort_p_recursive(base + piv * size, num - piv, size, compar, threshold);
        }
    } else {
        qsort_p_recursive(base, piv, size, compar, threshold);
        qsort_p_recursive(base + piv * size, num - piv, size, compar, threshold);
    }
}


void qsort_p(void* base, size_t num, size_t size, int (*compar)(const void*, const void*))
{
    int threshold, nested_saved;

    threshold = num / omp_get_max_threads() / 10; /* heuristic parameter */
    if (threshold < 2) {
        threshold = 2;
    }

    nested_saved = omp_get_nested();
    omp_set_nested(1);

    qsort_p_recursive(base, num, size, compar, threshold);

    omp_set_nested(nested_saved);
}
