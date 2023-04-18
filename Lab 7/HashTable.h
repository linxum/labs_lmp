#include <vector>
#include <iostream>
#include <algorithm>
#include "Contact.h"

using el = std::pair<int, Contact>;
using THashTable = std::vector<el>;
using Iterator = THashTable::iterator;

#pragma once
class HashTable
{
private:
	THashTable hashTable;
	size_t maxSize;
public:
	HashTable() :maxSize(2)
	{
		hashTable.resize(maxSize);
	}
	HashTable(std::ifstream& file);
	void rehash();
	size_t hash(unsigned long long key);
	Iterator find(unsigned long long key);
	bool remove(unsigned long long key);
	bool add(Contact good);
	void print();
	int count();
};
