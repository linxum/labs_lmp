#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
class Contact
{
	std::string name;
	std::string address[3];
	unsigned long long numPhone;
	int numBalance;
public:
	Contact();
	Contact(std::ifstream&);
	void print();
	int Compare(const Contact&);

	std::string GetName();
	unsigned long long GetPhone();
	std::string GetAddress();

};
