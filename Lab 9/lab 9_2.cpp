#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>

const size_t NTHREAD = 3;
std::atomic<int> res_sum(0);
std::atomic<int> res_line(-1);
size_t n = 0;
size_t m = 0;

int find_sum(int* arr)
{
	int sum = 0;
	for (int i = 0; i < m; i++)
	{
		sum += arr[i];
	}
	return sum;
}

void find_max_line(int** arr, int beg, int end)
{
	for (int i = beg; i < end; i++)
	{
		int sum = find_sum(arr[i]);
		if (sum > res_sum)
		{
			res_sum = sum;
			res_line = i;
		}

	}
}

int par_find_line(int** arr)
{
	std::thread th[NTHREAD - 1];
	size_t size = n / NTHREAD;

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		th[i] = std::thread(find_max_line, arr, i * size, (i + 1) * size);

	}


	for (int i = 0; i < NTHREAD - 1; i++)
	{
		th[i].join();
	}

	find_max_line(arr, (NTHREAD - 1) * size, n);
	return res_line;
}

void main()
{
	std::ifstream file("input.txt");
	int** arr;
	file >> n >> m;
	arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			file >> arr[i][j];
		}
	}
	std::cout << par_find_line(arr);
}
