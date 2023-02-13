#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Patient.h"
#include "Policlinic.h"
#include "Medic.h"

void init(Policlinic& policlinic, std::fstream& file)
{
	char t;
	std::string cat;
	int exp;
	std::string qual;
	while (file >> t)
	{
		std::string fio, is_sex;
		bool sex;
		file >> fio >> is_sex;
		if (is_sex == "м")
		{
			sex = true;
		}
		else
		{
			sex = false;
		}
		if (t == 'П')
		{
			int age, num_policy;
			file >> age >> num_policy;
			Patient ptn = Patient(fio, sex, age, num_policy);
			policlinic.add_by_order(std::move(std::make_shared<Patient>(ptn)));
		}
		else
		{
			std::string cat, qual;
			int exp;
			file >> qual >> exp >> cat;
			Medic mdc = Medic(fio, sex, exp, qual, Medic::str_to_type(cat));
			policlinic.add_by_order(std::move(std::make_shared<Medic>(mdc)));
		}
	}
	file.close();
}

std::string task(Policlinic& policlinic)
{
	std::string str;
	ps_ptr::iterator pediatr = policlinic.get_begin();
	int result = false;
	int f = 0, s = 0, h = 0, maxi = 0;
	while (pediatr != policlinic.get_end())
	{
		Medic* t = dynamic_cast<Medic*>(pediatr->get());

		if (t && t->get_qual() == "педиатр")
		{
			result = true;
			if (t->get_cat() == first)
				f++;
			else if (t->get_cat() == second)
				s++;
			else
				h++;
		}
		pediatr++;
	}
	maxi = max(max(f, s), h);
	if (maxi == f)
		str = "первая";
	else if (maxi == s)
		str = "вторая";
	else
		str = "высшая";
	return str;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::fstream file("input.txt");
	Policlinic policlinic("Electronic");
	init(policlinic, file);
	std::cout << policlinic << std::endl;
	std::cout << "" << task(policlinic);
}
