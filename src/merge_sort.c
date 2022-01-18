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
 * Copyright (C) 2022 Alessandro De Stefano (EarendilTiwele) Marco Della Rocca (marco741)
 * 
 * This file is part of OMP Mergesort implementation.
 * 
 * MPI Mergesort implementation is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MPI Mergesort implementation is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MPI Mergesort implementation.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @brief Utility used by _merge_sort_aux to implement the merging part in the merge sort
 * 
 * @param arr1 the first array to be merged
 * @param size1 the size of the first array
 * @param arr2 the second array to be merged
 * @param size2 the size of the second array
 * @param tmp the temporary array to implement the algorithm
 */
void _merge(int *arr1, int size1, int *arr2, int size2, int *tmp) {
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

  if (i < size1) {
      memcpy(tmp + i + j, arr1 + i, (size1 - i) * sizeof(int));
  }

  if (j < size2) {
      memcpy(tmp + i + j, arr1 + j, (size2 - j) * sizeof(int));
  }
  memcpy(arr1, tmp, (i + j) * sizeof(int));
}