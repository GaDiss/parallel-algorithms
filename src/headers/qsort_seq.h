//
// Created by Sergey Pankratov on 23.10.2021.
//

#ifndef PARALLEL_ALGORITHMS_QSORT_SEQ_H
#define PARALLEL_ALGORITHMS_QSORT_SEQ_H

#include <cstddef>

template<typename T>
size_t partition(T *a, size_t l, size_t r);

template<typename T>
void qsort_seq(T *a, size_t l, size_t r);

#endif //PARALLEL_ALGORITHMS_QSORT_SEQ_H
