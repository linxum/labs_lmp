#include <iostream>
#include <Windows.h>
#include <process.h>
#include <fstream>

const size_t NTHREAD = 3;
size_t n = 0;
size_t m = 0;

using INFORM = struct elem
{
	int** A;
	size_t beg, end;
	int max_sum = 0;
	int n_line = 0;
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

unsigned __stdcall find_max_line(void* arr)
{
	INFORM* inf = (INFORM*)arr;
	inf->n_line = 0;
	for (int i = inf->beg; i < inf->end; i++)
	{
		if (find_sum(inf->A[i]) > inf->max_sum)
		{
			inf->max_sum = find_sum(inf->A[i]);
			inf->n_line = i;
		}
	}
	_endthreadex(0);
	return 0;
}

int find_max_line(int** arr, int beg, int end, int& max_sum)
{
	int n_line = -1;
	for (int i = beg; i < end; i++)
	{
		if (find_sum(arr[i]) > max_sum)
		{
			max_sum = find_sum(arr[i]);
			n_line = i;
		}
			
	}
	return n_line;
}

int par_find_line(int** arr)
{
	HANDLE TH[NTHREAD - 1];
	unsigned THID[NTHREAD - 1];
	INFORM inf[NTHREAD - 1];
	size_t size = n / NTHREAD;

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		inf[i].A = arr;
		inf[i].beg = i * size;
		inf[i].max_sum = 0;
		inf[i].end = (i + 1) * size;
		TH[i] = (HANDLE)_beginthreadex(nullptr, 0, &find_max_line, &inf[i], 0, nullptr);
	}

	int max_sum = 0;
	int res_line = find_max_line(arr, (NTHREAD - 1) * size, n, max_sum);
	WaitForMultipleObjects(NTHREAD - 1, TH, true, INFINITE);

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		if (max_sum < inf[i].max_sum)
		{
			max_sum = inf[i].max_sum;
			res_line = inf[i].n_line;
		}
	}

	for (size_t i = 0; i < NTHREAD - 1; i++)
	{
		CloseHandle(TH[i]);
	}

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
