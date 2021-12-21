//
// Created by Sergey Pankratov on 21.12.2021.
//

#include "bench_bfs.h"

#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

/**
 * Finds distance between 'from' and 'to'.
 */
int bench_bfs(int (*bfs)(vector<vector<int>>&, int const, int const)) {
    int N = 400;
    int N2= N * N;
    int N3= N2 * N;

    int ITER = 5;
    int t_sum = 0;

    // adjacency list for cubic grid
    vector<vector<int>> edges(N3);
    for (int z = 0; z < N; z++) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                int v = x + N * y + N2 * z;
                int neighbours[] = {v - 1, v + 1, v - N, v + N, v - N2, v + N2};
                bool is_inner[] = {x > 0, x < N - 1, y > 0, y < N - 1, z > 0, z < N - 1,};
                for (int  j = 0; j < 6; j++) {
                    if (is_inner[j]) edges[v].push_back(neighbours[j]);
                }
            }
        }
    }

    cout << "Finding path in cubic graph with side " << N << endl;

    for (int i = 1; i <= ITER; i++) {

        auto t_start = high_resolution_clock::now();
        int dist = bfs(edges, 0, N3 - 1);
        auto t_finish = high_resolution_clock::now();
        int t = duration_cast<milliseconds>(t_finish - t_start).count();
        t_sum += t;

        // distance from (0, 0, 0) to (n - 1, n - 1, n - 1) is 3 * (n - 1)
        if (dist != 3 * (N - 1)) {
            cout << "FAILED: Incorrect bfs." << endl;
            return 1;
        }

        cout << "Iteration #" << i << " finished in " << t << " ms" << endl;
    }

    cout << "Testing BFS finished averaging " << t_sum / ITER << " ms over " << ITER << " iterations" << endl;

    return 0;
}
