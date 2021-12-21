//
// Created by Sergey Pankratov on 21.12.2021.
//

#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
#include "../src/bfs/bfs_par.h"
#include "../src/bfs/bfs_seq.h"

using namespace std;

typedef int (*Bfs)(vector<vector<int>>&, int const, int const);

// Testing class with parameterized sorting algorithm
class TestBfsParameterized : public ::testing::TestWithParam<Bfs> {
public:
    Bfs bfs = GetParam();

    vector<vector<int>> BuildAdjacencyList(int n, const vector<pair<int, int>>& edges) {
        vector<vector<int>> al(n);
        for (auto p : edges) {
            al[p.first].push_back(p.second);
            al[p.second].push_back(p.first);
        }
        return al;
    }

    void AssertBfsCorrectness(vector<vector<int>>& a, int const from, int const to,  int const expected) {
        int res = bfs(a, from, to);
        ASSERT_EQ(res, expected);
    }
};

TEST_P(TestBfsParameterized, SingleVertex) {
    vector<vector<int>> a = {{}};
    AssertBfsCorrectness(a, 0, 0, 0);
}

TEST_P(TestBfsParameterized, SingleEdge) {
    vector<vector<int>> a = {{1}, {0}};
    AssertBfsCorrectness(a, 0, 1, 1);
    AssertBfsCorrectness(a, 1, 0, 1);
    AssertBfsCorrectness(a, 1, 1, 0);
}

TEST_P(TestBfsParameterized, Square) {
    auto a = BuildAdjacencyList(4, {
        {0, 1}, {1, 2},
        {2, 3}, {3, 0}
    });
    AssertBfsCorrectness(a, 0, 2, 2);
    AssertBfsCorrectness(a, 1, 3, 2);
    AssertBfsCorrectness(a, 0, 3, 1);
}

TEST_P(TestBfsParameterized, Unreachable) {
    vector<vector<int>> a = {{}, {}};
    AssertBfsCorrectness(a, 0, 1, INT_MAX);
    AssertBfsCorrectness(a, 1, 0, INT_MAX);
}

auto select_random(const set<int> &s, size_t n) {
    auto it = begin(s);
    std::advance(it,n);
    return it;
}

TEST_P(TestBfsParameterized, RandomTree) {
    set<pair<int, int>> edges;
    set<int> s, u;
    int n = 1000;
    vector<int> d(n, INT_MAX);
    s.insert(0);
    for (int i = 1; i < n; i++) u.insert(i);
    d[0] = 0;

    random_device random_device;
    mt19937 random_engine(random_device());

    while (!u.empty()) {
        uniform_int_distribution<int> sd(0, s.size() - 1);
        uniform_int_distribution<int> ud(0, u.size() - 1);
        int v1 = *select_random(s, sd(random_engine));
        int v2 = *select_random(u, ud(random_engine));
        edges.insert({v1, v2});
        s.insert(v2);
        u.erase(v2);
        d[v2] = d[v1] + 1;
    }

    auto a = BuildAdjacencyList(n, vector<pair<int, int>>(edges.begin(), edges.end()));
    for (int i = 0; i < n; i++) {
        AssertBfsCorrectness(a, 0, i, d[i]);
    }
}

// Two instances for parallel and sequential qsort
INSTANTIATE_TEST_CASE_P(
        TestBfs,
        TestBfsParameterized,
        ::testing::Values(&bfs_seq, &bfs_par));

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

