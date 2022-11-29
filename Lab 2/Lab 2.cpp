#include <iostream>
#include "My_List.h"
#include <Windows.h>

void task(DLIST& list)
{
	int count = 1;
	ptrNODE p = list.get_begin();
	std::string cur_name = p->info.GetName();
	int cur_oper = p->info.GetPhone() / 10000000;
	while (p->next)
	{
		p = p->next;
		if (cur_name == p->info.GetName() && cur_oper == p->info.GetPhone() / 10000000)
		{
			count++;
		}
		else if (count >= 2)
		{
			std::cout << p->prev->info.GetName() << " " << p->prev->info.GetAddress() << std::endl;
			count = 1;
		}
		cur_name = p->info.GetName();
		cur_oper = p->info.GetPhone() / 10000000;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool flag = true;
	while (flag)
	{
		std::ifstream file("contact.txt");
		if (file)
		{
			DLIST list("contact.txt");
			file.close();
			list.print();
			task(list);
		}

		char choice;
		bool label = true;
		while (label)
		{
			std::cout << "Желаете начать заново или выйти? 1 - заново, 2 - выйти ";
			std::cin >> choice;
			switch (choice)
			{
			default:
				std::cout << "Неверный ввод!" << std::endl;
				label = true;
				break;
			case '1':
				flag = true;
				label = false;
				break;
			case '2':
				flag = false;
				label = false;
				break;
			}
		}
	}
	std::cin.get();
}
