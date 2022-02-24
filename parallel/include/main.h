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
 * This file is part of MPI Mergesort implementation.
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
 * @file main.h
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MAIN_H_
#define _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MAIN_H_

#define FILENAME "in.txt"

#include <stddef.h>


#define DEBUG 0
#define DEBUG_PUTS \
  if (DEBUG) puts

#define DEBUG_PRINT \
  if (DEBUG) printf

/**
 * @brief Print for debug of the elements of an array
 * 
 * @param arr the array to be printed
 * @param size the size of the array
 */
void debug_print_array(int* arr, size_t size);

#endif // _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MAIN_H_