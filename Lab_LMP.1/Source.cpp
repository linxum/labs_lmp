//Äàí òåêñòîâûé ôàéë input.txt, â êîòîðîì õðàíÿòñÿ öåëûå ÷èñëà. Ñîçäàòü óïîðÿäî÷åííûé ïî âîç -
//ðàñòàíèþ ñïèñîê.Èç êàæäîé ãðóïïû ïîäðÿä èäóùèõ ðàâíûõ ÷èñåë îòñòàâèòü òîëüêî îäíî(ïî -
//âòîðÿþùèåñÿ óäàëèòü).Ïîëó÷åííóþ ïîñëåäîâàòåëüíîñòü çàïèñàòü â òåêñòîâûé ôàéë
//output.txt.Åñëè èñêîìûõ ÷èñåë íåò, òî ïîìèìî ïîñëåäîâàòåëüíîñòè â ôàéë çàïèñàòü ñîîòâåò -
//ñòâóþùåå ñîîáùåíèå.

#include "My_List.h"
#include <Windows.h>

bool task(LIST& list)
{
	auto isEqual = [](int first, int second) // лямбда функция
	{
		return first == second;
	};
	bool check = false;
	ptrNODE p = list.get_head();
	while (p->next && p->next->next)
	{
		bool flag = true;
		if (isEqual(*p->next->info, *p->next->next->info))
		{
			list.del_after(p->next);
			flag = false;
		}
		if (flag)
		{
			p = p->next;
		}
		if (!flag)
		{
			check = true;
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
				std::cout << "Âûáåðèòå, êàê áóäåò ñîçäàâàòüñÿ ñïèñîê (1 - ñòåê, 2 - î÷åðåäü, 3 - óïîðÿäî÷åííî): "; std::cin >> choice;
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
					std::cout << "Íåâåðíûé ââîä" << std::endl;
					input = true;
					break;
				}
			}
			if (task(list))
			{
				list.print(file_out, "Ïðåîáðàçîâàííàÿ ïîñëåäîâàòåëüíîñòü: \n");
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
			std::cout << "Æåëàåòå íà÷àòü çàíîâî èëè âûéòè? 1 - çàíîâî, 2 - âûéòè ";
			std::cin >> choice;
			switch (choice)
			{
			default:
				std::cout << "Íåâåðíûé ââîä!" << std::endl;
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
