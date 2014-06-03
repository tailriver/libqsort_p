#pragma once
#ifndef QSORT_P_H
#define QSORT_P_H

#include <stdlib.h>

/**
 * A parallel quick sort routine using OpenMP.
 *
 * \param[inout] base An array to sort.
 * \param[in] num The length of array.
 * \param[in] size The size of array element.
 * \param[in] compar A comparator.
 */
void qsort_p(void* base, size_t num, size_t size, int (*compar)(const void*, const void*));

#endif /* QSORT_P_H */
