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
#include "merge_sort.h"

#include <math.h>
#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

/**
 * @brief Utility used by _merge_sort_aux to implement the merging part in the
 * merge sort
 *
 * @param arr1 the first array to be merged
 * @param size1 the size of the first array
 * @param arr2 the second array to be merged
 * @param size2 the size of the second array
 * @param tmp the temporary array to implement the algorithm
 */
void _merge(int *arr1, int size1, int *arr2, int size2, int *tmp, int maxsize) {
  int i = 0, j = 0;

  while (i < size1 && j < size2) {
    if (arr1[i] < arr2[j]) {
      tmp[i + j] = arr1[i];
      i++;
    } else {
      tmp[i + j] = arr2[j];
      j++;
    }
  }
  if (i < size1) memcpy(tmp + i + j, arr1 + i, (size1 - i) * sizeof(int));
  if (j < size2) memcpy(tmp + size1 + j, arr2 + j, (size2 - j) * sizeof(int));

  memcpy(arr1, tmp, MIN((size1 + size2), maxsize) * sizeof(int));
}

void merge_sort(int *arr, size_t n) {
  if (n <= 0) return;
  int rank, size, *padarr;
  size_t local_n;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Check if size is valid
  if (rank == 0 && size != 0 && (size & (size - 1))) {
    puts("Proccess number must be greater than zero and a power of two");
    exit(EXIT_FAILURE);
  }

  local_n = ceill((long double)n / size);

  if (rank == 0) {
    size_t padarr_size = local_n * size;
    padarr = malloc(padarr_size * sizeof(int));
    if (padarr == NULL) {
      puts("Memory could not be allocated");
      exit(EXIT_FAILURE);
    }
    memcpy(padarr, arr, n * sizeof(int));
    // Add padding
    for (size_t i = n; i < padarr_size; i++) {
      padarr[i] = __INT_MAX__;
    }
  } else {
    // Allocate local arrays for other processes
    arr = malloc((1 << trailing_zeros(rank)) * local_n * sizeof(int));
    if (arr == NULL) {
      puts("Memory could not be allocated");
      exit(EXIT_FAILURE);
    }
  }

  // Scatter workload
  MPI_Scatter(padarr, local_n, MPI_INT, arr, local_n, MPI_INT, 0,
              MPI_COMM_WORLD);
  _merge_sort_aux(arr, n, local_n, rank, size);
  if (rank == 0) free(padarr);
}

void _merge_sort_aux(int *arr, size_t n, size_t local_n, int rank, int size) {
  int partner, bitmask = 1, *arr2, *tmp;
  size_t arr_size;

  arr_size = (1 << trailing_zeros(rank | size)) * local_n;

  // sort first local_n elements
  tmp = malloc(arr_size * sizeof(int));
  if (tmp == NULL) {
    puts("Memory could not be allocated");
    exit(EXIT_FAILURE);
  }

  for (size_t curr_size = 1; curr_size <= local_n - 1; curr_size *= 2) {
    for (size_t left_start = 0; left_start <= local_n - curr_size - 1;
         left_start += 2 * curr_size) {
      // int left_size = MIN(curr_size, local_n - left_start);
      int right_size = MIN(curr_size, local_n - left_start - curr_size);

      // if (left_size < curr_size) break;
      _merge(arr + left_start, curr_size, arr + left_start + curr_size,
             right_size, tmp, local_n);
    }
  }

  arr2 = malloc(arr_size * 0.5 * sizeof(int));
  if (arr2 == NULL) {
    puts("Memory could not be allocated");
    exit(EXIT_FAILURE);
  }

  while (bitmask < size) {
    partner = rank ^ bitmask;
    if (rank > partner) {
      MPI_Send(arr, local_n, MPI_INT, partner, 0, MPI_COMM_WORLD);
      break;
    } else {
      MPI_Recv(arr2, local_n, MPI_INT, partner, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      _merge(arr, local_n, arr2, local_n, tmp, n);
      local_n *= 2;
      bitmask <<= 1;
    }
  }

  free(arr2);
  free(tmp);
}