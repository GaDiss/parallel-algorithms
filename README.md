# CW1 Quick Sort

Сравнение последовательной и параллельной реализации алгоритма быстрой сортировки.

## Задача

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
3. Запуск тестов
   * `make test`
4. Запустить бенчмарки
   * Для последовательного алгоритма: `CILK_NWORKERS=1 ./bench_seq`
   * Для параллельного алгоритма: `CILK_NWORKERS=4 ./bench_par`

### Вывод программы

* Последовательная версия

```
Sorting 100000000 integers:
Iteration #1 finished in 24359 ms
Iteration #2 finished in 24229 ms
Iteration #3 finished in 25841 ms
Iteration #4 finished in 25197 ms
Iteration #5 finished in 24232 ms
Sorting finished averaging 24771 ms over 5 iterations
```

* Параллельная версия

```
Sorting 100000000 integers:
Iteration #1 finished in 7923 ms
Iteration #2 finished in 8076 ms
Iteration #3 finished in 7988 ms
Iteration #4 finished in 7984 ms
Iteration #5 finished in 8224 ms
Sorting finished averaging 8039 ms over 5 iterations
```

## Итого

Параллельный алгоритм qsort на 4 потоках в среднем примерно в 3 раза бстрее последовательной реализации.