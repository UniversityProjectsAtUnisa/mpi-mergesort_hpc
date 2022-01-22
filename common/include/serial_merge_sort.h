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

#ifndef _HOME_MARCO741_MPI_CONTEST_MPI_COMMON_INCLUDE_SERIAL_MERGE_SORT_H_
#define _HOME_MARCO741_MPI_CONTEST_MPI_COMMON_INCLUDE_SERIAL_MERGE_SORT_H_

#include <stddef.h>

#define _merge(arr1, size1, arr2, size2, tmp) _merge_maxsize(arr1, size1, arr2, size2, tmp, __SIZE_MAX__);

void _merge_maxsize(int *arr1, size_t size1, int *arr2, size_t size2, int *tmp, size_t maxsize);
void serial_merge_sort(int *arr, size_t n);
void serial_merge_sort_tmp(int *arr, size_t n, int* tmp);

#endif // _HOME_MARCO741_MPI_CONTEST_MPI_COMMON_INCLUDE_SERIAL_MERGE_SORT_H_