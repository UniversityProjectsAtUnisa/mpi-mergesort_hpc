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
 * This file is part of MPI Mergesort implementation.
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
 * @file serial_merge_sort.c
 * @brief Implements a serial non-recursive version of the merge sort algorithm
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "serial_merge_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


/**
 * @brief Utility to implement the merging part in the merge sort algorithm
 * 
 * @param arr1 the first array to be merged
 * @param size1 the size of the first array
 * @param arr2 the second array to be merged
 * @param size2 the size of the second array
 * @param tmp the temporary array to implement the algorithm 
 * @param maxsize the maximum number of elements to copy in the final sorted array
 */
void _merge_maxsize(int* arr1, size_t size1, int* arr2, size_t size2, int* tmp,
                    size_t maxsize) {
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


/**
 * @brief Merge sorts an array of size n without parallel programming
 * 
 * @param arr the array to be sorted
 * @param n the size of the array
 */
void serial_merge_sort(int* arr, size_t n) {
  if (n == 0) return;
  int* tmp;

  tmp = malloc(n * sizeof(int));
  if (tmp == NULL) {
    puts("Memory could not be allocated");
    exit(EXIT_FAILURE);
  }

  serial_merge_sort_tmp(arr, n, tmp);
}


/**
 * @brief Merge sorts an array of size n without parallel programming, using an already allocated temporary array
 * 
 * @param arr the array to be sorted
 * @param n the size of the array
 * @param tmp the support array used in the implementation
 */
void serial_merge_sort_tmp(int* arr, size_t n, int* tmp) {
  if (n == 0) return;
  
  for (size_t curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
    for (size_t left_start = 0; left_start <= n - curr_size - 1;
         left_start += 2 * curr_size) {
      // int left_size = MIN(curr_size, n - left_start);
      int right_size = MIN(curr_size, n - left_start - curr_size);

      // if (left_size < curr_size) break;
      _merge_maxsize(arr + left_start, curr_size, arr + left_start + curr_size,
                     right_size, tmp, n);
    }
  }
}