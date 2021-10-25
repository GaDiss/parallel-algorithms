//
// Created by Sergey Pankratov on 22.10.2021.
//

#include "qsort_par.h"
#include "qsort_seq.h"

#include <cilk/cilk.h>
#include <algorithm>

using namespace std;

/**
 * Sorts elements of a in range [l, r] using paralleled
 * quick sort algorithm, using fork-join and
 * recursive divide and conquer.
 */
template<typename T>
void qsort_par(T *a, size_t l, size_t r) {
    if (r <= l) return;

    size_t m = partition(a, l, r);

    cilk_spawn qsort_par(a, l, m);
    qsort_par(a, ++m, r);
    cilk_sync;
}

template void qsort_par(long *a, size_t l, size_t r);
