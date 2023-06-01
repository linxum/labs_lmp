#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>

const size_t NTHREAD = 3;
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

void find_max_line(int** arr, int beg, int end, std::atomic<int>& max_sum, std::atomic<int>& n_line)
{
    for (int i = beg; i < end; i++)
    {
        int sum = find_sum(arr[i]);
        if (sum > max_sum)
        {
            max_sum = sum;
            n_line = i;
        }

    }
}

int par_find_line(int** arr)
{
    std::thread th[NTHREAD - 1];
    size_t size = n / NTHREAD;
    std::atomic<int> n_lines[NTHREAD - 1];
    std::atomic<int> max_sums[NTHREAD - 1];

    for (size_t i = 0; i < NTHREAD - 1; i++)
    {
        th[i] = std::thread(find_max_line, arr, i * size, (i + 1) * size, std::ref(max_sums[i]), std::ref(n_lines[i]));

    }

    std::atomic<int> max_sum(0);
    std::atomic<int> res_line(-1);
    find_max_line(arr, (NTHREAD - 1) * size, n, max_sum, res_line);

    for (int i = 0; i < NTHREAD - 1; i++)
    {
        th[i].join();
    }

    for (size_t i = 0; i < NTHREAD - 1; i++)
    {
        if (max_sum < max_sums[i])
        {
            max_sum.store(max_sums[i]);
            res_line.store(n_lines[i]);
        }
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
