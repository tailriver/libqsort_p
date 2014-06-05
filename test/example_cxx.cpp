#include <ctime>
#include <iostream>
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
    const size_t size = 10000;
    const size_t extract_size = 5;
    int *array;
    size_t i;

    array = new int[size];
    if (array == NULL) {
        std::cerr << "malloc error" << std::endl;
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    for (i = 0; i < size; ++i) {
        array[i] = rand();
    }

    std::cout << "Before sort: ";
    for (i = 0; i < extract_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "... ";
    for (i = size - extract_size; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    qsort_p(array, size, sizeof *array, comp_int);

    std::cout << "After sort: ";
    for (i = 0; i < extract_size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "... ";
    for (i = size - extract_size; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    delete[] array;
    return EXIT_SUCCESS;
}
