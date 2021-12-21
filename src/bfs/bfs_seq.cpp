//
// Created by Sergey Pankratov on 21.12.2021.
//

#include <climits>
#include <queue>
#include "bfs_seq.h"

using namespace std;

/**
 * Finds distance between 'from' and 'to'.
 */
int bfs_seq(vector<vector<int>>& edges, int const from, int const to) {
    const int INF = INT_MAX;
    int n = edges.size();

    vector<int> d(n, INF);
    d[from] = 0;

    queue<int> q;
    q.push(from);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : edges[u]) {
            if (d[v] == INF) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    return d[to];
}
