#include "HashTable.h"

HashTable::HashTable(std::ifstream& file)
{
	maxSize = 2;
	hashTable.resize(maxSize);
	for (auto x : hashTable)
		x.first = 0;
	while (!file.eof())
	{
		Contact ptr(file);
		add(ptr);
	}
	file.close();
}

void HashTable::rehash()
{
	bool result = false;
	if (count() > maxSize * 0.8)
	{
		maxSize *= 2;
		THashTable res;
		res.resize(maxSize);
		for (auto x : hashTable)
		{
			if (x.first == 1)
			{
				int index = hash(x.second.GetPhone());
				while (res[index].first == 1)
				{
					index = (index + 1) % maxSize;
				}
				res[index] = x;
			}
		}
		hashTable = res;
		result = true;
	}
	if (!result)
		std::cout << "not ";
	std::cout << "rehashed\n";
}

size_t HashTable::hash(unsigned long long key)
{
	return key % maxSize;
}

Iterator HashTable::find(unsigned long long key)
{
	Iterator It = std::find_if(hashTable.begin(), hashTable.end(), [&key](el elem)-> bool {return elem.first == 1 && elem.second.GetPhone() == key; });
	if (It == hashTable.end())
		std::cout << "not ";
	std::cout << "finded\n";
	return It;
}

bool HashTable::remove(unsigned long long key)
{
	bool result = false;
	Iterator It = find(key);
	if (It != hashTable.end())
	{
		result = true;
		(*It).first = -1;
	}
	if (!result)
		std::cout << "not ";
	std::cout << "removed\n";
	return result;
}

bool HashTable::add(Contact contact)
{
	bool result = false;
	if (find(contact.GetPhone()) == hashTable.end())
	{
		int index = hash(contact.GetPhone());
		while (hashTable[index].first == 1)
		{
			index = (index + 1) % maxSize;
		}
		hashTable[index].first = 1;
		hashTable[index].second = contact;
		result = true;
		rehash();
	}
	if (!result)
		std::cout << "not";
	std::cout << "added\n";
	return result;
}

void HashTable::print()
{
	for (int i = 0; i < maxSize; i++)
	{
		std::cout << i << ") ";
		if (hashTable[i].first == 1)
			hashTable[i].second.print();
		std::cout << "\n";
	}
}

int HashTable::count()
{
	int count = 0;
	for (auto x : hashTable)
	{
		if (x.first == 1)
			count++;
	}
	return count;
}