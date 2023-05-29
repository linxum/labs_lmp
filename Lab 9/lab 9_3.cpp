#include <iostream>
#include <fstream>
#include <future>

const size_t NTHREAD = 3;
size_t n = 0;
size_t m = 0;

struct Max_Line {
	int n_line = -1;
	int max_sum = 0;
};

int find_sum(int* arr)
{
	int sum = 0;
	for (int i = 0; i < m; i++)
	{
		sum += arr[i];
	}
	return sum;
}

Max_Line find_max_line(int** arr, int beg, int end)
{
	Max_Line line;
	for (int i = beg; i < end; i++)
	{
		if (find_sum(arr[i]) > line.max_sum)
		{
			line.max_sum = find_sum(arr[i]);
			line.n_line = i;
		}

	}
	return line;
}

int par_find_line(int** arr)
{
	std::future<Max_Line> th[NTHREAD - 1];
	size_t size = n / NTHREAD;

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		th[i] = std::async(std::launch::async, find_max_line, arr, i * size, (i + 1) * size);
	}

	Max_Line line = find_max_line(arr, (NTHREAD - 1) * size, n);


	Max_Line tmp;
	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		tmp = th[i].get();
		if (line.max_sum < tmp.max_sum)
		{
			line.max_sum = tmp.max_sum;
			line.n_line = tmp.n_line;
		}
	}
	return line.n_line;
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
