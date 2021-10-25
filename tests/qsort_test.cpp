//
// Created by Sergey Pankratov on 25.10.2021.
//

#include <gtest/gtest.h>
#include <qsort_par.h>
#include <qsort_seq.h>

typedef void (*Qsort)(long *, size_t const, size_t const);

// Testing class with parameterized sorting algorithm
class TestQSortParameterized : public ::testing::TestWithParam<Qsort> {
public:
    Qsort sort = GetParam();

    void AssertSortCorrectness(long a[], size_t const size) {
        sort(a, 0, size - 1);
        for (size_t i = 1; i < size; i++) {
            ASSERT_LE(a[i - 1], a[i]);
        }
    }
};

TEST_P(TestQSortParameterized, Singleton) {
    const size_t N = 1;
    long a[N] = {1};
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, SwapTwo) {
    const size_t N = 2;
    long a[N] = {2, 1};
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, ConstValue) {
    const size_t N = 1000;
    long a[N] = {0 };
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, Reverse) {
    const size_t N = 9;
    long a[N] = {9, 8, 7, 6, 5, 4, 3, 2, 1 };
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, AlreadySorted) {
    const size_t N = 9;
    long a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, ShiftedLeft) {
    const size_t N = 9;
    long a[N] = {2, 3, 4, 5, 6, 7, 8, 9, 1 };
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, ShiftedRight) {
    const size_t N = 9;
    long a[N] = {9, 1, 2, 3, 4, 5, 6, 7, 8 };
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, Tricky) {
    const size_t N = 9;
    long a[N] = { 2, 4, 6, 8, 9, 7, 5, 3, 1 };
    AssertSortCorrectness(a, N);
}

TEST_P(TestQSortParameterized, Random) {
    const size_t N = 1e2;
    const int ITER = 1e4;
    for (int i = 1; i <= ITER; i++) {
        long *a = new long[N];
        for (int j = 0; j < N; j++) a[j] = random();
        AssertSortCorrectness(a, N);
        delete[] a;
    }
}

// Two instances for parallel and sequential qsort
INSTANTIATE_TEST_CASE_P(
        TestQSort,
        TestQSortParameterized,
        ::testing::Values(&qsort_seq<long>, &qsort_par<long>));

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
