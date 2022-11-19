#include<iostream>
#include <vector>
#include <cstdlib> 
#include<iomanip>
#include <ctime>
#include <omp.h>

using namespace std;

void writeMatrix(const char* path) {
	FILE* f;
	int size_row_A, size_col_A;
	cout << "       Enter size_row:";
	cin >> size_row_A;
	cout << "       Enter size_col:";
	cin >> size_col_A;
	fopen_s(&f, path, "w");
	fprintf(f, "%d", size_row_A);
	fprintf(f, "%5d", size_col_A);
	for (int i = 0; i < size_row_A; ++i)
	{
		for (int j = 0; j < size_col_A; ++j)
		{
			fprintf(f, "%2d", rand() % 10);
		}
	}
	fclose(f);
}

int main() {
	srand(time(0));
	FILE* f;
	int size_row_A, size_col_A, size_row_B, size_col_B, l = 0;
	int N = 3;
	vector<int> matrixA(N * N);
	vector<int> matrixB(N * N);
	vector<int> result(N * N);

	cout << "Enter Matrix A:\n";
	writeMatrix("C:/Users/vuong/Desktop/inputA.txt");

	cout << "Enter Matrix B:\n";
	writeMatrix("C:/Users/vuong/Desktop/inputB.txt");

	//read matrix A
	fopen_s(&f, "C:/Users/vuong/Desktop/inputA.txt", "r");
	if (f != NULL)
	{
		fscanf_s(f, "%d", &size_row_A); //i
		fscanf_s(f, "%d", &size_col_A);
	}
	printf("Matrix A in file:\n");
	for (int i = 0; i < size_row_A; ++i)
	{
		for (int j = 0; j < size_col_A; ++j)
		{
			fscanf_s(f, "%d", &matrixA[i * size_col_A + j]);
			printf("%3d", matrixA[i * size_col_A + j]);
		}
		printf("\n");
	}
	fclose(f);

	//read matrix B
	fopen_s(&f, "C:/Users/vuong/Desktop/inputB.txt", "r");
	if (f != NULL)
	{
		fscanf_s(f, "%d", &size_row_B); //i
		fscanf_s(f, "%d", &size_col_B);
	}
	printf("Matrix B in file:\n");
	for (int i = 0; i < size_row_B; ++i)
	{
		for (int j = 0; j < size_col_B; ++j)
		{
			fscanf_s(f, "%d", &matrixB[i * size_col_B + j]);
			printf("%3d", matrixB[i * size_col_B + j]);
		}
		printf("\n");
	}
	fclose(f);

	//mulMatrix
	if (size_col_A != size_row_B)
		cout << "Error!" << endl;
	else {
		printf("Matrix result:\n");
		int threadsNum = 2;
		omp_set_num_threads(threadsNum);
//#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
#pragma omp parallel for
		for (int i = 0; i < size_row_A; ++i)
		{
			for (int j = 0; j < size_col_B; ++j)
			{
				result[i * size_col_B + j] = 0;
				for (int k = 0; k < size_col_B; k++) {
					result[i * size_col_B + j] += (matrixA[i * size_col_A + k] * matrixB[k * size_col_B + j]);
				}
				printf("%5d", result[i * size_col_B + j]);
			}
			printf("\n");
		}
	}

	//write result

	fopen_s(&f, "C:/Users/vuong/Desktop/output.txt", "w");
	for (int i = 0; i < size_row_A; ++i)
	{
		for (int j = 0; j < size_col_B; ++j)
		{
			fprintf(f, "%10d", result[i * size_col_A + j]);
		}

		fprintf(f, "%c", '\n');
	}
	fclose(f);

	cout << "runtime = " << clock() / 1000.0 << endl;

	return 0;
}