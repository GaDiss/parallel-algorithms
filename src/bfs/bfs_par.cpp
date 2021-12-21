//
// Created by Sergey Pankratov on 21.12.2021.
//

#include <climits>
#include <datapar.hpp>

#include "bfs_seq.h"

/**
 * Finds distance between 'from' and 'to'.
 */
int bfs_par(std::vector<std::vector<int>> &edges, int const from, int const to) {
    const int INF = INT_MAX;
    int n = edges.size();

    // array of distances from start
    pasl::pctl::parray<int> d(n, INF);
    d[from] = 0;

    // frontier
    pasl::pctl::parray<int> f = {from};
    int f_size = 1;

    int iter = 1;
    while (true) {
        pasl::pctl::parray<int> f2_block_sizes(f_size, [&edges, &f](int i) { return edges[f[i]].size(); });
        // f2_pref_sizes[i] = number of neighbours for all nodes in frontier before i
        pasl::pctl::parray<long> f2_pref_sizes = pasl::pctl::scan(f2_block_sizes.begin(), f2_block_sizes.end(), 0L,
                                         [](long x, long y) { return x + y; }, pasl::pctl::forward_exclusive_scan
                                         );
        long f2_size = f2_pref_sizes[f_size - 1] + f2_block_sizes[f_size - 1];
        // next frontier
        pasl::pctl::parray<int> f2(f2_size, INF);

        pasl::pctl::parallel_for(0, f_size, [&f, &edges, &f2, &f2_pref_sizes, &d, &iter](int i) {
            int v = f[i];
            for (int j = 0; j < edges[v].size(); j++) {
                int u = edges[v][j];
                int inf = INF;
                if (__atomic_compare_exchange_n(&d[u], &inf, iter, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
                    f2[f2_pref_sizes[i] + j] = u;
                }
            }
        });

        f = pasl::pctl::filter(f2.begin(), f2.end(), [](int x) { return x != INF; });
        f_size = (int) f.size();

        if (f_size == 0) break;
        iter++;
    }

    return d[to];
}
