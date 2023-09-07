#include <iostream>
#include <fstream>
#include <omp.h>

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

int par_find_line(int** arr)
{
	int res_line = -1;
	int max_sum = 0;

	omp_lock_t lock;
	omp_init_lock(&lock);

#pragma omp parallel shared(arr)
	{
		int loc_line = -1;
		int loc_sum = 0;
#pragma omp for schedule(static, 4)
		for (int i = 0; i < n; i++)
		{
			if (find_sum(arr[i]) > loc_sum)
			{
				loc_sum = find_sum(arr[i]);
				loc_line = i;
			}
		}

		omp_set_lock(&lock);
		if (loc_sum > max_sum)
		{
			res_line = loc_line;
			max_sum = loc_sum;
		}
		
		std::cout << "Line: " << loc_line << "; Sum: " << loc_sum << std::endl;

		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
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
