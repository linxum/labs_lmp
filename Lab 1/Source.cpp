//Дан текстовый файл input.txt, в котором хранятся целые числа. Создать упорядоченный по воз -
//растанию список.Из каждой группы подряд идущих равных чисел отставить только одно(по -
//вторяющиеся удалить).Полученную последовательность записать в текстовый файл
//output.txt.Если искомых чисел нет, то помимо последовательности в файл записать соответ -
//ствующее сообщение.

#include "My_List.h"
#include <Windows.h>

bool task(LIST& list)
{
	auto isEqual = [](int first, int second)
	{
		return first == second;
	};
	bool check = false;
	ptrNODE p = list.get_head()->next;
	while (p && p->next)
	{
		if (isEqual(*p->info, *p->next->info))
		{
			list.del_after(p);
			check = true;
		}
		else
		{
			p = p->next;
		}
	}
	return check;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool flag = true;
	while (flag)
	{
		LIST list;
		std::ifstream file_in("input.txt");
		std::ofstream file_out("output.txt");
		if (file_in)
		{
			bool input = true;
			while (input)
			{
				char choice;
				std::cout << "Выберите, как будет создаваться список (1 - стек, 2 - очередь, 3 - упорядоченно): "; std::cin >> choice;
				switch (choice)
				{
				case '1':
					list.create_by_stack(file_in);
					input = false;
					break;
				case '2':
					list.create_by_queue(file_in);
					input = false;
					break;
				case '3':
					list.create_by_order(file_in);
					input = false;
					break;
				default:
					std::cout << "Неверный ввод" << std::endl;
					input = true;
					break;
				}
			}
			if (task(list))
			{
				list.print(file_out, "Преобразованная последовательность: \n");
			}
			else
			{
				list.print(file_out);
			}
		}

		file_in.close();
		file_out.close();

		char choice;
		bool label = true;
		while (label)
		{
			std::cout << "Желаете начать заново или выйти? (1 - заново, 2 - выйти): ";
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
	std::cin.ignore();
	std::cin.get();
}
