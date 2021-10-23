# CW1 Quick Sort

Сравнение последовательной и параллельной реализации алгоритма быстрой сортировки.

##Задача

Требуется написать
последовательную версию алгоритма (seq) и параллельную
версию (par). Взять случайный массив из 10^8 элементов и
отсортировать. (Усреднить по 5 запускам) Сравнить время работы
par на 4 процессах и seq на одном процессе.

## Сборка и запуск проекта

Для запуска необходимо:
1. Установить последнюю версию [OpenCilk](https://github.com/OpenCilk/opencilk-project)
2. Собрать проект при помощи CMake 
   * `CC=<Path to clang> CXX=<Path to clang++> cmake .`
   * `make`
3. Запустить бенчмарки
   * Для последовательного алгоритма: `CILK_NWORKERS=1 ./bench_seq`
   * Для параллельного алгоритма: `CILK_NWORKERS=4 ./bench_par`

### Вывод программы

* Последовательная версия

```
Sorting 100000000 integers:
Iteration #1 finished in 22352 ms
Iteration #2 finished in 23157 ms
Iteration #3 finished in 22113 ms
Iteration #4 finished in 23447 ms
Iteration #5 finished in 22220 ms
Sorting finished averaging 22657 ms over 5 iterations
```

* Параллельная версия

```
Sorting 100000000 integers:
Iteration #1 finished in 7562 ms
Iteration #2 finished in 8580 ms
Iteration #3 finished in 8031 ms
Iteration #4 finished in 7901 ms
Iteration #5 finished in 7898 ms
Sorting finished averaging 7994 ms over 5 iterations
```

## Итого

Параллельный алгоритм qsort на 4 потоках в среднем примерно в 3 раза бстрее последовательной реализации.