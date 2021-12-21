//
// Created by Sergey Pankratov on 22.10.2021.
//

#include "qsort_seq.h"

#include<algorithm>

using namespace std;

/**
 * Moves elements of a in range [l, r] and returns m,
 * such that for every i in range [l, m],
 * and for every j in range [m + 1, r], a[i] <= a[j].
 */
template<typename T>
size_t partition(T *a, size_t l, size_t r) {
    T v = a[(l + r) / 2];
    while (l <= r) {
        while (a[l] < v) l++;
        while (a[r] > v) r--;
        if (l >= r) break;
        swap(a[l++], a[r--]);
    }
    return r;
}

/**
 * Sorts elements of a in range [l, r] using sequential
 * quick sort algorithm, using recursive divide and conquer.
 */
template<typename T>
void qsort_seq(T *a, size_t l, size_t r) {
    if (r <= l) return;

    size_t m = partition(a, l, r);

    qsort_seq(a, l, m);
    qsort_seq(a, ++m, r);
}

template size_t partition(long *a, size_t l, size_t r);
template void qsort_seq(long *a, size_t l, size_t r);