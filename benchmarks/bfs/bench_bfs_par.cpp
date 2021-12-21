//
// Created by Sergey Pankratov on 21.12.2021.
//

#include "bench_bfs.h"
#include "../../src/bfs/bfs_par.h"

int main() {
    return bench_bfs(&bfs_par);
}