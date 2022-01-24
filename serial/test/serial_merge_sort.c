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
 * @file serial_merge_sort.c
 * @brief tests serial_merge_sort behaviour
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "serial_merge_sort.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Verifies if the elements in an array are sorted in ascending order
 *
 * @param arr the array to check
 * @param size the length of the array
 * @return int 0 if the array is not sorted, else 1
 */
int _is_sorted(int *arr, int size) {
  for (int i = 0; i < size - 1; i++)
    if (arr[i] > arr[i + 1]) return 0;
  return 1;
}

/**
 * @brief Copies the value contained in an array stored in the stack to an array
 * stored in the heap
 *
 * @param heap_array the array stored in the heap
 * @param stack_array the array stored in the stack
 * @param size the size of the stack array
 */
void _load_from_stackarr(int *heap_array, int *stack_array, int size) {
  for (size_t i = 0; i < size; i++) heap_array[i] = stack_array[i];
}

/**
 * @brief Verifies if the elements in heap_array and stack_array are equal
 * 
 * @param heap_array the array stored in the heap
 * @param stack_array the array stored in the stack
 * @param size the size of the stack array
 * @return int one if they are equal, zero otherwise
 */
int _equals_with_stackarr(int *heap_array, int *stack_array, int size) {
  for (size_t i = 0; i < size; i++)
    if (heap_array[i] != stack_array[i]) return 0;
  return 1;
}

/**
 * @brief Verifies if the given array is correctly sorted by the merge_sort and
 * its resulting elements are equal to the given solution
 *
 * @param stack_arr the array to check
 * @param solution the expected result
 * @param size the size of the arrays
 */
void _test_merge_sort(int *stack_arr, int *solution, int size) {
  int *arr = malloc(size * sizeof(int));
  _load_from_stackarr(arr, stack_arr, size);

  serial_merge_sort(arr, size);
  assert(_equals_with_stackarr(arr, solution, size) == 1);
  assert(_is_sorted(arr, size) == 1);
}

/**
 * @brief Tests merge_sort with an empty array
 *
 */
void test_empty_array() {
  int size = 0;
  int stack_arr[0] = {};
  int solution[0] = {};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort call with an array with one element
 *
 */
void test_one_element() {
  int size = 1;
  int stack_arr[1] = {1};
  int solution[1] = {1};
  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort call with an array whose elements are in reverse
 * order
 *
 */
void test_descendent() {
  int size = 5;
  int stack_arr[5] = {5, 2, -1, -4, -6};
  int solution[5] = {-6, -4, -1, 2, 5};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort call with an array whose elements are all different
 * from each other
 *
 */
void test_full_different() {
  int size = 5;
  int stack_arr[5] = {5, -1, 4, 2, -6};
  int solution[5] = {-6, -1, 2, 4, 5};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort call with an array whose elements are all equal from
 * each other
 *
 */
void test_full_equals() {
  int size = 5;
  int stack_arr[5] = {42, 42, 42, 42, 42};
  int solution[5] = {42, 42, 42, 42, 42};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort call with an array in which some elements are equal
 *
 */
void test_some_equals() {
  int size = 5;
  int stack_arr[5] = {5, -1, 5, 2, 6};
  int solution[5] = {-1, 2, 5, 5, 6};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort call with an array whose elements are all positive
 *
 */
void test_full_positive() {
  int size = 5;
  int stack_arr[5] = {5, 1, 4, 2, 6};
  int solution[5] = {1, 2, 4, 5, 6};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort with an array in which every element is negative
 *
 */
void test_full_negative() {
  int size = 5;
  int stack_arr[5] = {-5, -1, -4, -2, -6};
  int solution[5] = {-6, -5, -4, -2, -1};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort with an array whose elements are already in order
 *
 */
void test_ordered() {
  int size = 5;
  int stack_arr[5] = {-3, -2, 1, 5, 6};
  int solution[5] = {-3, -2, 1, 5, 6};

  _test_merge_sort(stack_arr, solution, size);
}

/**
 * @brief Tests merge_sort giving the wrong size as argument
 *
 */
void test_fail_n() {
  int size = 5;
  int stack_arr[5] = {-2, -3, 1, 6, 5};
  int solution[5] = {-3, -2, 1, 5, 6};

  int *arr = malloc(size * sizeof(int));
  _load_from_stackarr(arr, stack_arr, size);

  serial_merge_sort(arr, 2);
  assert(_equals_with_stackarr(arr, solution, size) == 0);
}

int main(int argc, char *argv[]) {
  test_empty_array();
  test_one_element();
  test_descendent();
  test_full_different();
  test_full_equals();
  test_some_equals();
  test_full_positive();
  test_full_negative();
  test_ordered();
  test_fail_n();
  return 0;
}