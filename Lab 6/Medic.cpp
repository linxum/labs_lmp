#include "Medic.h"

Medic::Medic(std::string fio, bool sex, int exp, std::string qual, Type cat): Person(fio, sex), exp(exp), qual(qual), cat(cat) {};

Type Medic::get_cat()
{
	return cat;
}

int Medic::get_exp()
{
	return exp;
}

std::string Medic::get_qual()
{
	return qual;
}

void Medic::set_cat(std::string str)
{
	cat = str_to_type(str);
}

void Medic::set_exp(int val)
{
	exp = val;
}

void Medic::set_qual(std::string val)
{
	qual = val;
}

std::string Medic::Get_type_string()
{
	switch (cat)
	{
	case first:
		return "первая";
		break;
	case second:
		return "вторая";
		break;
	case highest:
		return "высшая";
		break;
	}
}

Type Medic::str_to_type(std::string str)
{
	if (str == "первая")
		return first;
	else if (str == "вторая")
		return second;
	else if (str == "высшая")
		return highest;
		
}

std::string Medic::toString()
{
	return "Врач: " + Person::toString() + ", " + Get_type_string() + ", стаж: " + std::to_string(exp) + ", " + qual;

}
