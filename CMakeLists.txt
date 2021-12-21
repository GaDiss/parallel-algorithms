cmake_minimum_required(VERSION 3.17)
project(parallel_algorithms)
set(CMAKE_CXX_STANDARD 17)

# OpenCilk
add_compile_options(-fcilkplus -DUSE_CILK_PLUS_RUNTIME)

include_directories(pctl/include cmdline/include chunkedseq/include)
set(SOURCES
        benchmarks/qsort/bench_qsort.cpp
        src/qsort/qsort_seq.cpp
        src/qsort/qsort_par.cpp
        benchmarks/bfs/bench_bfs.cpp
        src/bfs/bfs_seq.cpp
        src/bfs/bfs_par.cpp
        )

# sequential quick sort benchmark executable
add_executable(bench_qsort_seq benchmarks/qsort/bench_qsort_seq.cpp ${SOURCES})
target_link_libraries(bench_qsort_seq cilkrts)

# parallel quick sort benchmark executable
add_executable(bench_qsort_par benchmarks/qsort/bench_qsort_par.cpp ${SOURCES})
target_link_libraries(bench_qsort_par cilkrts)

# sequential bfs sort benchmark executable
add_executable(bench_bfs_seq benchmarks/bfs/bench_bfs_seq.cpp ${SOURCES})
target_link_libraries(bench_bfs_seq cilkrts)

# parallel quick sort benchmark executable
add_executable(bench_bfs_par benchmarks/bfs/bench_bfs_par.cpp ${SOURCES})
target_link_libraries(bench_bfs_par cilkrts)

# Google tests
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.8.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_qsort tests/qsort_test.cpp ${SOURCES})
target_link_libraries(test_qsort gtest_main cilkrts)


add_executable(test_bfs tests/bfs_test.cpp ${SOURCES})
target_link_libraries(test_bfs gtest_main cilkrts)

include(GoogleTest)
gtest_discover_tests(test_qsort test_bfs)

