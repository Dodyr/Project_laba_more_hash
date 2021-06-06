#include "Header1.h"

/*Library::Library(std::ifstream& fin)
{
	std::getline(fin, name);
	while (!fin.eof())
	{
		char ch = fin.get();
		fin.ignore();
		std::string name;
		int number_of_pages;
		std::string publishing_house;
		getline(fin, name);
		fin >> number_of_pages;
		fin.ignore();
		getline(fin, publishing_house);
		Publication* new_public;
		switch (ch)
		{
		case 'b':
		{
			std::string author;
			std::string genre;
			std::string binding;
			fin >> author >> genre >> binding;
			fin.ignore();
			new_public = new Book(name, number_of_pages, publishing_house, author, genre, binding);
			break;
		}
		case 'j':
		{
			int number;
			int year;
			std::string web_site;
			fin >> number >> year >> web_site;
			fin.ignore();
			new_public = new Journal(name, number_of_pages, publishing_house, number, year, web_site);
			break;
		}
		}
		fin.ignore();
		list_publications.push_back(new_public);
	}
}


Library::~Library()
{
	std::for_each(list_publications.begin(), list_publications.end(), Destroyer());
}

TList Library::getList()
{
	return list_publications;
}

void Library::setList(TList list)
{
	list_publications = list;
}

void Library::print()
{
	std::cout << name << '\n';
	std::cout << "==============================\n";
	for (TIterator it = list_publications.begin(); it != list_publications.end(); it++)
	{
		(*it)->print();
	}
}

void Library::sort_()
{
	auto cmp = [](Publication* a, Publication* b)->bool {return a->GetNPages() < b->GetNPages(); };
	list_publications.sort(cmp);
}*/

Hash_table::Hash_table()
{
	for (int i = 0; i < n; i++)
	{
		std::list<Publication*> lst;
		table.push_back(lst);
	}
}

void Hash_table::Add(Publication* p)
{
	int index = Hash((*p).getName());
	table[index].push_back(p);
}

int Hash_table::Hash(std::string key)
{
	int sum = 0;
	for (int i = 0; i < key.size(); i++)
		sum += key[i];
	sum = sum % n;
	return sum;
}

Publication* Hash_table::Find(std::string key, bool& res)
{
	int index = Hash(key);
	TIterator it = table[index].begin();
	res = false;
	while (it != table[index].end())
	{
		if ((*it)->getName() == key)
		{
			res = true;
			return *it;
		}
		else
			it++;
	}
	return NULL;
}

bool Hash_table::Delete(std::string key)
{
	int index = Hash(key);
	TIterator it = table[index].begin();
	bool found = false;
	while (it != table[index].end() && !found)
	{
		if ((*it)->getName() == key)
		{
			it = table[index].erase(it);
			found = true;
		}
		else
			it++;
	}
	return found;
}

Sorter Hash_full(std::ifstream& fin, Hash_table& table)
{
	Sorter library;
	while (!fin.eof())
	{
		char ch = fin.get();
		fin.ignore();
		std::string name;
		int number_of_pages;
		std::string publishing_house;
		getline(fin, name);
		fin >> number_of_pages;
		fin.ignore();
		getline(fin, publishing_house);
		Publication* new_public;
		switch (ch)
		{
		case 'b':
		{
			std::string author;
			std::string genre;
			std::string binding;
			fin >> author >> genre >> binding;
			fin.ignore();
			new_public = new Book(name, number_of_pages, publishing_house, author, genre, binding);
			table.Add(new_public);
			library.push_back(name);
			break;
		}
		case 'j':
		{
			int number;
			int year;
			std::string web_site;
			fin >> number >> year >> web_site;
			fin.ignore();
			new_public = new Journal(name, number_of_pages, publishing_house, number, year, web_site);
			table.Add(new_public);
			library.push_back(name);
			break;
		}
		}
		fin.ignore();
	}
	return library;
}

void print_(Sorter sorter, Hash_table table)
{
	for (IterarotSort it = sorter.begin(); it != sorter.end(); it++)
	{
		bool found;
		Publication* p = table.Find((*it), found);
		p->print();
	}
}