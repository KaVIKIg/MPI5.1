#include <stdio.h>
#include "mpi.h"
using namespace std;
#include <stdio.h>
#include <time.h>
//#include <malloc.h>
#include <random>
#include <iostream>
using namespace std;
#define N 24

int* merge(int* First, int Fsize, int* Second, int Ssize);
void sort(int* A, int begin, int end);

int* merge(int* First, int Fsize, int* Second, int Ssize) 
{
	int fi = 0, si = 0, mi = 0, i;
	int* merged;
	int Msize = Fsize + Ssize;

	merged = (int*)malloc(Msize * sizeof(int));
	while ((fi < Fsize) && (si < Ssize)) 
	{
		if (First[fi] <= Second[si]) 
		{
			merged[mi] = First[fi];
			mi++; fi++;
		}
		else 
		{
			merged[mi] = Second[si];
			mi++; si++;
		}
	}

	if (fi >= Fsize)
		for (i = mi; i < Msize; i++, si++)
			merged[i] = Second[si];
	else if (si >= Ssize)
		for (i = mi; i < Msize; i++, fi++)
			merged[i] = First[fi];

	for (i = 0; i < Fsize; i++)
		First[i] = merged[i];
	for (i = 0; i < Ssize; i++)
		Second[i] = merged[Fsize + i];

	return merged;
}

void sort(int* Arr, int start, int end)
{
	int* sortedArr;
	int mid = (start + end) / 2;
	int leftCount = mid - start+1;
	int rightCount = end - mid;

	/* Если диапазон состоит из одного элемента, он уже отсортирован */
	if (end == start) 
	{
		return;
	}
	else 
	{
		
		sort(Arr, start, mid);
		
		sort(Arr, mid + 1, end);
		 
		sortedArr = merge(Arr + start, leftCount, Arr + mid + 1, rightCount);
	}
}


int main(int* argc, char** argv)
{
	int* data;
	int* local_data;
	int* otherArr;
	int q, n = N;
	int my_rank, comm_sz;
	int local_n = 0;
	int i;
	int local_n1 = 0;
	int local_n2 = 0;
	int step;
	double start, stop;
	MPI_Status status;

	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	start = clock();
	MPI_Comm comm1;
	MPI_Comm comm2;
	MPI_Comm comm3;
	MPI_Comm comm4;
	MPI_Comm comm5;
	MPI_Comm comm6;
	MPI_Comm comm7;
	MPI_Comm comm8;

	MPI_Group group;
	MPI_Group group1;
	MPI_Group group2;
	MPI_Group group3;
	MPI_Group group4;
	MPI_Group group5;
	MPI_Group group6;
	MPI_Group group7;
	
	MPI_Comm_dup(MPI_COMM_WORLD, &comm1);
	MPI_Comm_group(comm1, &group);
	
	
	
	int* ranks = new int[6];
	for (i = 0; i < 6; i++) 
	{
		ranks[i] = i + 1;
	}
	
	MPI_Group_incl(group, 6, ranks, &group1);
	MPI_Comm_create(comm1, group1, &comm2);
	
	int* ranks1 = new int[5];
	
	ranks1[0] = 0;
	ranks1[1] = 3;
	ranks1[2] = 4;
	ranks1[3] = 5;
	ranks1[4] = 6;
	MPI_Group_excl(group, 2, ranks1, &group2);
	MPI_Comm_create(comm1, group2, &comm3);


	int* ranks2 = new int[2];
	ranks2[0] = 3;
	ranks2[1] = 4;
	
	MPI_Group_incl(group, 2, ranks2, &group3);
	MPI_Comm_create(comm1, group3, &comm4);

	
	int* ranks3 = new int[2];
	ranks3[0] = 5;
	ranks3[1] = 6;
	
	MPI_Group_incl(group, 2, ranks3, &group4);
	MPI_Comm_create(comm1, group4, &comm5);

	int* ranks4 = new int[2];
	
		ranks4[0] = 1;
		ranks4[1] = 3;
	

	MPI_Group_incl(group, 2, ranks4, &group5);
	MPI_Comm_create(comm1, group5, &comm6);

	int* ranks5 = new int[2];

	ranks5[0] = 1;
	ranks5[1] = 5;


	MPI_Group_incl(group, 2, ranks5, &group6);
	MPI_Comm_create(comm1, group6, &comm7);
	
	
	int* ranks7 = new int[2];
	for (i = 0; i < 2; i++) {
		ranks7[i] = i ;
		
	}

	MPI_Group_incl(group, 2, ranks7, &group7);
	MPI_Comm_create(comm1, group7, &comm8);
	
	int r;
	local_n = n / (comm_sz-1);
	r = n % (comm_sz-1);
	int size = n + local_n - r;
	data = (int*)malloc((size) * sizeof(int));
	for (i = 0; i < n; i++)
		data[i] = rand() % 1000;
	
		cout << endl;

	if (my_rank == 0)
	{
		
		for (i = 0; i < n; i++)
			cout << " " << data[i];
		cout << endl;
		for (i = 1; i < comm_sz; i++)
		{
			// 0 отправляет 1, 2, 3, 4, 5, 6
			MPI_Send(&local_n, 1, MPI_INT, i, 0, comm1);
			
		}
		
	}
	
	else
	{
		//1, 2, 3, 4, 5, 6 принимают от 0
		MPI_Recv(&local_n, 1, MPI_INT, 0, 0, comm1, &status);
		local_data = (int*)malloc(local_n * sizeof(int));

		//1, 2, 3, 4, 5, 6
		MPI_Scatter(data, local_n, MPI_INT, local_data, local_n, MPI_INT, 1, comm2);
		sort(local_data, 0, local_n - 1);
		
		if (my_rank == 1)
		{
			//1 принимает от 2
			MPI_Bcast(&q, 1, MPI_INT, 1, comm3);
			otherArr = (int*)malloc(q * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, q, MPI_INT, 1, comm3);
			local_data = merge(local_data, local_n, otherArr, q);
			local_n = local_n + q;



			//1 принимает от 3
			MPI_Bcast(&q, 1, MPI_INT, 1, comm6);
			otherArr = (int*)malloc(q * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, q, MPI_INT, 1, comm6);
			local_data = merge(local_data, local_n, otherArr, q);
			local_n = local_n + q;


			//1 принимает от 5
			MPI_Bcast(&q, 1, MPI_INT, 1, comm7);
			otherArr = (int*)malloc(q * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, q, MPI_INT, 1, comm7);
			local_data = merge(local_data, local_n, otherArr, q);
			local_n = local_n + q;

			//1 отправляет 0
			MPI_Send(&local_n, 1, MPI_INT, 0, 0, comm8);
			MPI_Send(local_data, local_n, MPI_INT, 0, 0, comm8);
		}



		if (my_rank == 2)
		{
			//2 отправляет 1
			MPI_Bcast(&local_n, 1, MPI_INT, 1, comm3);
			otherArr = (int*)malloc(local_n * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, local_n, MPI_INT, 1, comm3);

		}


		if (my_rank == 3)
		{

			// 3 принимает от 4
			MPI_Bcast(&q, 1, MPI_INT, 1, comm4);
			otherArr = (int*)malloc(q * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, q, MPI_INT, 1, comm4);
			local_data = merge(local_data, local_n, otherArr, q);
			local_n = local_n + q;

			//3 отправляет 1
			MPI_Bcast(&local_n, 1, MPI_INT, 1, comm6);
			otherArr = (int*)malloc(local_n * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, local_n, MPI_INT, 1, comm6);


		}



		if (my_rank == 4)
		{
			//4 отправляет 3
			MPI_Bcast(&local_n, 1, MPI_INT, 1, comm4);
			otherArr = (int*)malloc(local_n * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, local_n, MPI_INT, 1, comm4);

		}


		if (my_rank == 5)
		{
			//5 принимает от 6
			MPI_Bcast(&q, 1, MPI_INT, 1, comm5);
			otherArr = (int*)malloc(q * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, q, MPI_INT, 1, comm5);
			local_data = merge(local_data, local_n, otherArr, q);
			local_n = local_n + q;

			//5 отправляет 1
			MPI_Bcast(&local_n, 1, MPI_INT, 1, comm7);
			otherArr = (int*)malloc(local_n * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, local_n, MPI_INT, 1, comm7);

		}


		if (my_rank == 6)
		{
			//6 отправляет 5
			MPI_Bcast(&local_n, 1, MPI_INT, 1, comm5);
			otherArr = (int*)malloc(local_n * sizeof(int));
			MPI_Scatter(local_data, local_n, MPI_INT, otherArr, local_n, MPI_INT, 1, comm5);

		}


	}

	

	if (my_rank == 0)
	{

		//0 принимает от 1 результат и выводит
		MPI_Recv(&q, 1, MPI_INT, 1, 0, comm8, &status);
		MPI_Recv(data, q, MPI_INT, 1, 0, comm8, &status);
		stop = clock();
		printf("\nArray with %d; %d processors, took %f second\n\n", n, comm_sz, (stop - start) / CLOCKS_PER_SEC);

		for (i = 0; i < q; i++)
			cout << " " << data[i];
	}

	
	MPI_Comm_free(&comm1);
	//MPI_Comm_free(&comm2);
	/*MPI_Comm_free(&comm3);
	MPI_Comm_free(&comm4);*/
	MPI_Finalize();
}