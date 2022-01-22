#include "main.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "serial_merge_sort.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  int* arr;
  char* filename;
  size_t n;
  double start, end;
  filename = (argc > 1) ? argv[1] : FILENAME;

  read_size_from_file(filename, &n);
  DEBUG_PRINT("n: %ld\n", n);
  arr = malloc(n * sizeof(int));
  if (arr == NULL) {
    puts("Memory could not be allocated");
    exit(EXIT_FAILURE);
  }
  read_values_from_file(n, filename, arr);
  debug_print_array(arr, n);

  start = clock();
  serial_merge_sort(arr, n);
  end = clock();

  debug_print_array(arr, n);

  printf("%f", (end - start) / CLOCKS_PER_SEC);

  return EXIT_SUCCESS;
}

/**
 * @brief Print for debug of the elements of an array
 *
 * @param arr the array to be printed
 * @param size the size of the array
 */
void debug_print_array(int* arr, size_t size) {
  if (DEBUG) {
    for (size_t i = 0; i < size; i++) {
      printf("%d\n", arr[i]);
    }
  }
}