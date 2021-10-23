//
// Created by Sergey Pankratov on 23.10.2021.
//

#ifndef PARALLEL_ALGORITHMS_BENCH_QSORT_H
#define PARALLEL_ALGORITHMS_BENCH_QSORT_H

#include <cstddef>

int bench_qsort(void (*qsort)(long *, size_t const, size_t const));

#endif //PARALLEL_ALGORITHMS_BENCH_QSORT_H
