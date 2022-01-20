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

#include "main.h"

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "merge_sort.h"
#include "utils.h"

int main(int argc, char const* argv[]) {
  int rank, size, *arr;
  size_t n, local_n;
  char* filename;
  // TODO: MPI_Wtime

  // Initialization
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Check if size is valid
  if (size != 0 && (size & size - 1)) {
    puts("Proccess number must be greater than zero and a power of two");
    exit(EXIT_FAILURE);
  }

  // Reading array size as root process
  if (rank == 0) {
    filename = (argc > 1) ? argv[1] : FILENAME;
    read_size_from_file(filename, &n);
  }
  // Broadcasting array size and calculate local array size
  MPI_Bcast(&n, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
  local_n = ceill((long double)n / size);

  if (rank == 0) {
    // Read array values as root process
    arr = malloc(local_n * size * sizeof(int));
    if (arr == NULL) {
      puts("Memory could not be allocated");
      exit(EXIT_FAILURE);
    }
    read_values_from_file(n, filename, arr);
    // Add padding
    for (size_t i = n; i < local_n * size; i++) {
      arr[i] = __INT_MAX__;
    }
    debug_print_array(arr, n);
    DEBUG_PUTS("");
  } else {
    // Allocate local arrays for other processes
    arr = malloc((1 << trailing_zeros(rank)) * local_n * sizeof(int));
    if (arr == NULL) {
      puts("Memory could not be allocated");
      exit(EXIT_FAILURE);
    }
  }
  // Scatter workload
  MPI_Scatter(arr, local_n, MPI_INT, arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);
  // qsort(arr, local_n, sizeof(int), compare);

  merge_sort(arr, n, local_n, rank, size, MPI_COMM_WORLD);

  MPI_Finalize();

  if (rank == 0) debug_print_array(arr, n);
  if (rank == 0) {
    for (size_t i = 0; i < n - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        printf("FAIL");
        return 0;
      }
    }
    puts("SUCCESS");
  }
  free(arr);

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