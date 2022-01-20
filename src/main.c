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
  int rank, size, *arr, *subarr;
  size_t *n, local_n;
  // TODO: p potenza di 2?
  // MPI_Wtime

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    char* filename = (argc > 1) ? argv[1] : FILENAME;
    read_file(&arr, n, filename);
  }
  MPI_Bcast(n, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

  
  local_n = ceil(*n / size);
  if (rank != 0) {
    arr = malloc((1 << trailing_zeros(rank)) * local_n * sizeof(int));
  } else {
    debug_print_array(arr, n);
  }
  // size must be power of 2

  subarr = malloc(local_n * sizeof(int));
  MPI_Scatter(arr, local_n, MPI_INT, subarr, local_n, MPI_INT, 0,
              MPI_COMM_WORLD);
  qsort(subarr, local_n, sizeof(int), compare);
  // TODO: Change

  // sleep(rank);
  // debug_print_array(subarr, local_n);
  memcpy(arr, subarr, local_n * sizeof(int));
  printf("\n");

  merge_sort(arr, local_n, rank, size, MPI_COMM_WORLD);

  // printf("hello world\n");
  MPI_Finalize();
  // printf("finito %d\n", rank);

  if (rank == 0) debug_print_array(arr, n);
  free(arr);
  free(subarr);
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