cmake_minimum_required(VERSION 3.17)
project(parallel_algorithms)
set(CMAKE_CXX_STANDARD 17)

link_directories(cilk/lib)
include_directories(cilk/include)
include_directories(cilk/src/include)
include_directories(src/headers benchmarks/headers)

add_compile_options(-fcilkplus)

set(SOURCES benchmarks/bench_qsort.cpp src/qsort_seq.cpp src/qsort_par.cpp)

add_executable(bench_seq benchmarks/bench_qsort_seq.cpp ${SOURCES})
target_link_libraries(bench_seq cilkrts)

add_executable(bench_par benchmarks/bench_qsort_par.cpp ${SOURCES})
target_link_libraries(bench_par cilkrts)
