//
// Created by Sergey Pankratov on 23.10.2021.
//

#include "bench_qsort.h"
#include "qsort_par.h"

int main() {
    return bench_qsort(&qsort_par<long>);
}
