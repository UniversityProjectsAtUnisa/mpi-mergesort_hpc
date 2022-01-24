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
 * @file utils.c
 * @brief Contains utilities to read from file and to count trailing zeros of a number
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Counts the traling zeros in the binary representation of an integer; 
 * returns -1 if the input is 0
 * 
 * @param n the input integer
 * @return int the number of traling zeros, -1 if the input is 0
 */
int trailing_zeros(int n) {
  int count = 0;

  if (n == 0) return -1;
  while (n > 0 && (n & 1) == 0) {
    count++;
    n >>= 1;
  }

  return count;
}


/**
 * @brief Reads the size of an array in file "filename"
 * 
 * @param filename the name of the input file
 * @param size the size to be filled with the value read from the file
 */
void read_size_from_file(char* filename, size_t* size) {
  FILE* fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    puts("Input file not found");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%ld\n", size);
  fclose(fp);
}


/**
 * @brief Reads the values of an array in file "filename"
 * 
 * @param size the size of the array, so the number of values to read from file
 * @param filename the name of the input file
 * @param arr the array to be filled with the data from the file
 */
void read_values_from_file(size_t size, char* filename, int* arr) {
  FILE* fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    puts("Input file not found");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%*d\n");

  for (size_t i = 0; i < size; i++) {
    fscanf(fp, "%d", arr + i);
  }
  fclose(fp);
}
