//
// Created by Sergey Pankratov on 22.10.2021.
//

#include "qsort_seq.h"

#include<algorithm>

using namespace std;

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

template<typename T>
void qsort_seq(T *a, size_t l, size_t r) {
    if (r <= l) return;

    size_t m = partition(a, l, r);

    qsort_seq(a, l, m);
    qsort_seq(a, ++m, r);
}

template void qsort_seq(long *a, size_t l, size_t r);