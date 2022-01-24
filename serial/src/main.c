/*
 * Course: High Performance Computing 2021/2022
 *
 * Lecturer: Francesco Moscato    fmoscato@unisa.it
 *
 * Group:
 * De Stefano Alessandro   0622701470  a.destefano56@studenti.unisa.it
 * Della Rocca Marco   0622701573  m.dellarocca22@studenti.unisa.it
 *
 * MPI implementation of mergesort algorithm
 * Copyright (C) 2022 Alessandro De Stefano (EarendilTiwele) Marco Della Rocca
 * (marco741)
 *
 * This file is part of OMP Mergesort implementation.
 *
 * MPI Mergesort implementation is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPI Mergesort implementation is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MPI Mergesort implementation.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file main.c
 * @brief measures the execution time of a serial implementation of the merge_sort algorithm
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "serial_merge_sort.h"
#include "utils.h"


/**
 * @brief Calls and measures the execution time of merge_sort function
 * 
 * @param argc number of arguments
 * @param argv arguments. Accepts filename as first argument, defaults to "in.txt"
 * @return int status code 
 */
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