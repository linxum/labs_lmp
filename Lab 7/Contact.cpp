#include "Contact.h"

Contact::Contact()
{
	name = "";
	address[0] = "";
	address[1] = "";
	address[2] = "";
	numPhone = 0;
	numBalance = 0;
}

Contact::Contact(std::ifstream& input_file)
{
	const char SEP = ',';
	std::string separator;
	std::string q_address;
	std::getline(input_file, name);
	std::getline(input_file, q_address);
	std::stringstream ss(q_address);
	std::getline(ss, address[0], SEP);
	std::getline(ss, address[1], SEP);
	std::getline(ss, address[2], SEP);
	input_file >> numPhone;
	input_file >> numBalance;
	input_file.ignore();
	std::getline(input_file, separator);
}

void Contact::print()
{
	std::cout << name << std::endl;
	std::cout << address[0] << " " << address[1] << " " << address[2] << std::endl;
	std::cout << numPhone << std::endl;
	std::cout << numBalance << std::endl;
	std::cout << "----------" << std::endl;
}

int Contact::Compare(const Contact& object)
{
	int result = 1;
	if (name < object.name
		|| name == object.name && numPhone > object.numPhone
		|| name == object.name && numPhone == object.numPhone && address[0] > object.address[0])
	{
		result = -1;
	}
	else if (name == object.name && numPhone == object.numPhone && address[0] == object.address[0])
	{
		result = 0;
	}
	return result;
}

std::string Contact::GetName()
{
	return name;
}

unsigned long long Contact::GetPhone()
{
	return numPhone;
}

std::string Contact::GetAddress()
{
	std::string addr = address[0] + " " + address[1] + " " + address[2];
	return addr;
}