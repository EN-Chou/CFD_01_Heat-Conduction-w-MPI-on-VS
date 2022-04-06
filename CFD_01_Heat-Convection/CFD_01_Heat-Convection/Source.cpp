#include <iostream>
#include <mpi.h>
#include <math.h>
#include "write.h"
#define PI 3.1415926
#define N 11
using namespace std;

int main(int argc, char* argv[]) {
	int rank;
	int size;
	MPI_Status istat[8];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	/*Implementation*/

	//Problem Description
	int m_no = N;
	double m_grid[N][N] = { 0 };
	int i = 0, j = 0;
	double residual = 1;
	double residual_after = 1;
	double tol = pow(10, -7);
	double temp = 0;
	int processor = 4; //非必要，size即可得知:	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int partition[5] = { 0,(N - 1) / 4 * 1,(N - 1) / 4 * 2,(N - 1) / 4 * 3,(N - 1) / 4 * 4 };
	int iterations = 0;

	if (size == 1)
		partition[1] = (N - 1);



	//Initialization
	for (i = 0; i < m_no; i++) {
		m_grid[i][0] = 0;
		m_grid[i][m_no - 1] = 0;
		m_grid[m_no - 1][i] = 0;
		m_grid[0][i] = sin(PI * i / (m_no - 1));
	}

	//main
	double time1 = MPI_Wtime();
	while (residual > tol) {
		iterations++;
		residual = 0;
		for (i = partition[rank]; i < partition[rank + 1]; i++) {
			for (j = 1; j < m_no - 1; j++) {
				if (i == 0)
					break;
				temp = m_grid[i][j];
				m_grid[i][j] = (m_grid[i - 1][j] + m_grid[i + 1][j] + m_grid[i][j - 1] + m_grid[i][j + 1]) * 0.25;
				residual = residual + abs(m_grid[i][j] - temp);
			}
		}
		// mpi allreduce -> summation (residual)
		//MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(&residual, &residual_after, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);//suceed confirm

		residual = residual_after;
		// mpi wait and bcast individual
		//MPI_Barrier(MPI_COMM_WORLD);
		for (i = 0; i < size; i++) {
			MPI_Bcast(&m_grid[partition[i]][0], (m_no - 1) / processor * m_no, MPI_DOUBLE, i, MPI_COMM_WORLD);//currently fail
		}
		//cout << "partition["<<rank<<"]:	" << partition[rank] << endl;
		/*
		if ((rank == 0)) {
			cout << "iterations:	" << iterations ;
			cout << "	residual:	" << residual << endl;

		}*/

	}


	double time2 = MPI_Wtime() - time1;
	if (rank == 0) {
		cout << "iterations:	" << iterations << endl;
		cout << "residual:	" << residual << endl;
		cout << "Time: " << time2 << endl << endl;
		write(&m_grid[0][0], m_no, m_no);

	}

	/*-------------*/

	MPI_Finalize();
	cout << "MPI_Finalize()" << endl;
	return 0;
}

