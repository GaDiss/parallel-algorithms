//
// Created by Sergey Pankratov on 23.10.2021.
//

#include "bench_qsort.h"

#include <chrono>
#include <iostream>

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

bool assert_sorted(const long *a, size_t l, size_t r) {
    for (size_t i = l + 1; i < r; i++) {
        if (a[i - 1] > a[i]) return false;
    }
    return true;
}

int bench_qsort(void (*qsort)(long *, size_t const, size_t const)) {

    size_t N = 1e8;
    int ITER = 5;
    int t_sum = 0;

    cout << "Sorting " << N << " integers:" << endl;

    for (int i = 1; i <= ITER; i++) {
        long *a = new long[N];
        for (int j = 0; j < N; j++) a[j] = random();

        auto t_start = high_resolution_clock::now();
        qsort(a, 0, N);
        auto t_finish = high_resolution_clock::now();
        int t = duration_cast<milliseconds>(t_finish - t_start).count();
        t_sum += t;

        if (!assert_sorted(a, 0, N)) {
            cout << "FAILED: Incorrect sorting." << endl;
            return 1;
        }

        cout << "Iteration #" << i << " finished in " << t << " ms" << endl;

        delete[] a;
    }

    cout << "Sorting finished averaging " << t_sum / ITER << " ms over " << ITER << " iterations" << endl;

    return 0;
}
