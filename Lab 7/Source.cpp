#include "HashTable.h"
#include <Windows.h>
#include <fstream>

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream file("list.txt");
	HashTable Table(file);
	Table.print();
	std::cout << '\n';

	unsigned long long check = 9192884868;
	Table.remove(check);
	Table.print();
	std::cout << '\n';

	unsigned long long check1 = 9202884868;
	Contact res = Table.find_if(check1);

	std::ifstream file1("list1.txt");
	Contact ptr(file1);
	Table.add(ptr);
	Table.print();
}
