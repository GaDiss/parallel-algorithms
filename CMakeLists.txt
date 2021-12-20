cmake_minimum_required(VERSION 3.17)
project(parallel_algorithms)
set(CMAKE_CXX_STANDARD 17)

# OpenCilk
add_compile_options(-fcilkplus)

include_directories(src/headers benchmarks/headers)
set(SOURCES benchmarks/qsort/bench_qsort.cpp src/qsort/qsort_seq.cpp src/qsort/qsort_par.cpp)

# sequential benchmark executable
add_executable(bench_seq benchmarks/qsort/bench_qsort_seq.cpp ${SOURCES})
target_link_libraries(bench_seq cilkrts)

# parallel benchmark executable
add_executable(bench_par benchmarks/qsort/bench_qsort_par.cpp ${SOURCES})
target_link_libraries(bench_par cilkrts)

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
include(GoogleTest)
gtest_discover_tests(test_qsort)

