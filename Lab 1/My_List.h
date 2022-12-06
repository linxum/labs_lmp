#pragma once//ñëåäèò ïîäêëþ÷åíà áèáëèîòåêà èëè íåò (÷òîáû íå áûëî ïîâòîðîíîãî ïîäêëþ÷åíèÿ)
#include <iostream>
#include <fstream>

using TInfo = int;//ââîä ïñåâäîíèìà

struct NODE //còðóêòóðà óçëà
{
	TInfo* info;
	NODE* next;//ïîëå, õðàíÿùåå ñëåäóþùèé óçåë 
	NODE(TInfo value, NODE* ptr = nullptr) :next(ptr) //êîíñòðóêòîð
	{
		info = new int;
		*info = value;
	}
	~NODE()//äåñòðóêòîð
	{
		next = nullptr;
		delete info;
		info = nullptr;
	}
};

using ptrNODE = NODE*;//ïñåâäîíèì óçëà

struct LIST
{
private:
	ptrNODE head, tail;//ñîçäàíèå çàãëàâíîãî è ïîñëåäíåãî óçëà
	size_t size;
	void adding_by_pointer(ptrNODE& ptr, TInfo elem)
	{
		ptrNODE p = new NODE(elem, ptr);
		ptr = p;
	}
	void deleting_by_pointer(ptrNODE& ptr)
	{
		ptrNODE p = ptr;
		ptr = p->next;
		delete p;
	}
public:
	LIST()//êîíñòðóêòîð
	{
		head = new NODE(0);
		tail = head;
		size = 0;
	}
	//ìåòîäû
	~LIST();
	ptrNODE get_head()//çàïðîñ ãîëîâû (â òàñêå, ÷òîáû ïîÿâèëîñü íà÷àëî ñïèñêà)
	{
		return head;
	}
	TInfo get_first()
	{
		return *head->next->info;
	}
	size_t get_size()
	{
		return size;
	}
	ptrNODE get_tail()
	{
		return tail;
	}
	void set_tail(ptrNODE ptr)
	{
		tail = ptr;
	}
	bool empty();
	void add_to_head(TInfo elem);
	void add_to_tail(TInfo elem);
	void add_after(ptrNODE ptr, TInfo elem);
	void del_from_head();
	void del_after(ptrNODE ptr);
	void create_by_stack(std::ifstream& file);
	void create_by_queue(std::ifstream& file);
	void create_by_order(std::ifstream& file);
	void print(std::ofstream& file, const char* message = "Èñêîìîé ïîñëåäîâàòåëüíîñòè íå îáðóæåíî\n");
	void sorting();//cîðòèðîâêà ïî âîçðàñòàíèþ
};
