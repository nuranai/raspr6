#include <iostream>
#include <omp.h>
#include <chrono>

//const int N = 5, M = 4, threadNum = 2;
const int N = 100, M = 80, threadNum = 4;

int main()
{
	int** a = new int*[N], ** b = new int* [M], ** c = new int *[N];
	for (int i = 0; i < N; i++) {
		a[i] = new int[M];
		c[i] = new int[N];
		for (int j = 0; j < M; j++) {
			a[i][j] = 1;
		}
		for (int j = 0; j < N; j++) {
			c[i][j] = 0;
		}
	}
	for (int i = 0; i < M; i++) {
		b[i] = new int[N];
		for (int j = 0; j < N; j++) {
			b[i][j] = 2;
		}
	}
	int i = 0;
	auto start = std::chrono::system_clock::now();

#pragma omp parallel for private(i) num_threads(2)
	for (i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < M; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}

	auto end = std::chrono::system_clock::now();

	std::cout << "time taken:: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < N; j++) {
	//		std::cout << c[i][j] << ' ';
	//	}
	//	std::cout << std::endl;
	//}

	for (int i = 0; i < N; i++) {
		delete[] a[i];
		delete[] c[i];
	}
	for (int i = 0; i < M; i++) {
		delete[] b[i];
	}
	delete[]a;
	delete[]b;
	delete[]c;
}
