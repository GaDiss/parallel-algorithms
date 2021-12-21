//
// Created by Sergey Pankratov on 21.12.2021.
//

#ifndef PARALLEL_ALGORITHMS_BENCH_BFS_H
#define PARALLEL_ALGORITHMS_BENCH_BFS_H

#include <cstddef>
#include <vector>

int bench_bfs(int (*bfs)(std::vector<std::vector<int>>&, int const, int const));

#endif //PARALLEL_ALGORITHMS_BENCH_BFS_H
