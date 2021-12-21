//
// Created by Sergey Pankratov on 21.12.2021.
//

#include "bench_bfs.h"
#include "../../src/bfs/bfs_seq.h"

int main() {
    return bench_bfs(&bfs_seq);
}