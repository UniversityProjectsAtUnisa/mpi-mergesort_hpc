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
 * @file utils.h
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _HOME_MARCO741_MPI_CONTEST_MPI_COMMON_INCLUDE_UTILS_H_
#define _HOME_MARCO741_MPI_CONTEST_MPI_COMMON_INCLUDE_UTILS_H_

#include <stddef.h>

#define MIN(a, b) (a < b ? a : b)

/**
 * @brief Counts the traling zeros in the binary representation of an integer; 
 * returns -1 if the input is 0
 * 
 * @param n the input integer
 * @return int the number of traling zeros, -1 if the input is 0
 */
int trailing_zeros(int n);

/**
 * @brief Reads the size of an array in file "filename"
 * 
 * @param filename the name of the input file
 * @param size the size to be filled with the value read from the file
 */
void read_size_from_file(char* filename, size_t* size);

/**
 * @brief Reads the values of an array in file "filename"
 * 
 * @param size the size of the array, so the number of values to read from file
 * @param filename the name of the input file
 * @param arr the array to be filled with the data from the file
 */
void read_values_from_file(size_t size, char* filename, int* arr);

#endif  // _HOME_MARCO741_MPI_CONTEST_MPI_COMMON_INCLUDE_UTILS_H_