#ifndef _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MERGE_SORT_H_
#define _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MERGE_SORT_H_

#include <mpi.h>

void _merge(int *arr1, int size1, int *arr2, int size2, int *tmp);
void merge_sort(int *A, int local_n, int my_rank, int p, MPI_Comm comm);


#endif // _HOME_MARCO741_MPI_CONTEST_MPI_INCLUDE_MERGE_SORT_H_