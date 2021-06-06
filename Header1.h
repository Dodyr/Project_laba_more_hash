#pragma once

#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <Windows.h>
#include <list>

#include "Header2.h"

using TVect = std::vector<std::list<Publication*>>;
using TIterator = std::list<Publication*>::iterator;
using Sorter = std::list<std::string>;
using IterarotSort = std::list<std::string>::iterator;

/*class Library
{
private:
	std::string name;
	TList list_publications;
public:
	Library(std::ifstream& fin);
	~Library();
	TList getList();
	void setList(TList list);
	void print();
	void sort_();
};*/

struct Hash_table
{
	int n = 23;
	TVect table;
	int Hash(std::string key);
	Hash_table();
	//~Hash_table();
	void Add(Publication* p);
	Publication* Find(std::string key, bool& found);
	bool Delete(std::string key);
};

Sorter Hash_full(std::ifstream& fin, Hash_table& table);
void print_(Sorter sorter, Hash_table table);
