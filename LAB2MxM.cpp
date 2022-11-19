#include<iostream>
#include <vector>
#include <cstdlib> 
#include<iomanip>
#include <ctime>
#include <omp.h>

using namespace std;

void writeMatrix(const char* path, int size) {
	FILE* f;
	fopen_s(&f, path, "w");
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			fprintf(f, "%10d", rand() % 10);
	fclose(f);
}

int main() {
	srand(time(0));
	FILE* f;
	int i, j, l = 0;
	int N = 100;
	vector<int> matrixA(N * N);
	vector<int> matrixB(N * N);
	vector<int> result(N * N);

	writeMatrix("C:/Users/vuong/Desktop/inputA.txt", N);

	writeMatrix("C:/Users/vuong/Desktop/inputB.txt", N);

	//read matrix A
	fopen_s(&f, "C:/Users/vuong/Desktop/inputA.txt", "r");
	if (f != NULL) {
		printf("Matrix A in file:\n");
		for (i = 0; i < N; ++i)
		{
			for (j = 0; j < N; ++j)
			{
				fscanf_s(f, "%d", &matrixA[i * N + j]);
				printf("%10d", matrixA[i * N + j]);
			}
			printf("\n");
		}
		fclose(f);
	}

	//read matrix B
	fopen_s(&f, "C:/Users/vuong/Desktop/inputB.txt", "r");
	if (f != NULL) {
		printf("Matrix B in file:\n");
		for (i = 0; i < N; ++i)
		{
			for (j = 0; j < N; ++j)
			{
				fscanf_s(f, "%d", &matrixB[i * N + j]);
				printf("%10d", matrixB[i * N + j]);
			}
			printf("\n");
		}
		fclose(f);
	}

	//mulMatrix
	printf("Matrix result:\n");
	int threadsNum = 3;
	omp_set_num_threads(threadsNum);
	//#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
#pragma omp parallel for
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			result[i * N + j] = 0;
			for (int k = 0; k < N; k++) {
				result[i * N + j] += (matrixA[i * N + k] * matrixB[k * N + j]);
			}
			printf("%10d", result[i * N + j]);
		}
		printf("\n");
	}

	//write result
	fopen_s(&f, "C:/Users/vuong/Desktop/output.txt", "w");
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			fprintf(f, "%10d", result[i * N + j]);
		}
	}
	fclose(f);

	cout << "\nruntime = " << clock() / 1000.0 << endl;

	return 0;
}