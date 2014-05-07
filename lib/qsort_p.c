#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int comp_int(const void* a, const void* b)
{
    int aa = *(int*) a;
    int bb = *(int*) b;

    if (aa < bb) return 1;
    if (aa > bb) return -1;
    return 0;
}


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


void qsort_p(void* base, size_t num, size_t size, int (*compar)(const void*, const void*))
{
    if (num == 1) return;

    #pragma omp critical
    {
    int i;
    int rank;
    rank = omp_get_thread_num();
    printf("rank %d: [%d]", rank, num);
    for (i = 0; i < num; ++i) {
        printf(" %d", ((int*)base)[i]);
    }
    printf("\n");
    }

    if (num == 2) {
        printf("a=%d b=%d\n", *(int*)base, *(int*)(base+size));
        printf("compar: %d\n", compar(base, base + size));
        if (compar(base, base + size) == -1) {
            swap(base, base + size, size);
        }
        return;
    }

    if (num > 1) {
        int comp1, comp2;
        int mid, end;
        mid = num / 2;
        end = num - 1;

        comp1 = compar(base, base + mid * size);
        comp2 = compar(base + mid * size, base + end * size);
        /*
         *  0  * : end <= mid = beg or beg = mid <= end
         *  *  0 : beg <= mid = end or end = mid <= beg
         *  1  1 : beg < mid < end
         * -1 -1 : end > mid > beg
         *  1 -1 : beg < end < mid or end < beg < mid
         * -1  1 : mid < beg < end or mid < end < beg
         */
        if (comp1 == 0 || comp2 == 0 || comp1 + comp2 != 0) {

        } else {
            int comp3;
            comp3 = compar(base, base + end * size);

        }

  //      pivots[0] = base

        #pragma omp parallel sections
        {
            #pragma omp section
            qsort_p(base, mid, size, compar);
            #pragma omp section
            qsort_p(base + mid * size, num - mid, size, compar);
        }
    }
}


int main(void)
{
    int threads;
    int a[256], i;

    threads = omp_get_max_threads();
    omp_set_nested(1);
    printf("max_threads = %d\n", threads);

    for (i = 0; i < 256; ++i)
        a[i] = 255 - i;

    qsort_p(a, 256, sizeof(*a), comp_int);

    for (i = 0; i < 256; ++i)
        printf("%d ", a[i]);
    printf("\n");
}
