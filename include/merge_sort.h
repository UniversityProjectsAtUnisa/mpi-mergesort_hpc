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


#ifndef _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MERGE_SORT_H_
#define _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MERGE_SORT_H_

#include <mpi.h>
#include <stddef.h>

void _merge(int *arr1, int size1, int *arr2, int size2, int *tmp, int maxsize);
void merge_sort(int *arr, size_t n);
void _merge_sort_aux(int *A, size_t n, size_t local_n, int rank, int size);


#endif // _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MERGE_SORT_H_