#include "Header1.h"

Publication::Publication(std::string name, int number_of_pages, std::string publishing_house)
{
	this->name = name;
	this->number_of_pages = number_of_pages;
	this->publishing_house = publishing_house;
}

int Publication::GetNPages()
{
	return number_of_pages;
}

std::string Publication::getName()
{
	return name;
}

int Publication::Compare(Publication* p)
{
	int res = -1;
	if (p->number_of_pages == number_of_pages)
		res = 0;
	else
		if (number_of_pages > p->number_of_pages)
			res = 1;
	return res;
}

void Publication::print()
{
	std::cout << name << ' ' << number_of_pages << ' ' << publishing_house << std::endl;
}

bool Publication::operator()(Publication* p1, Publication* p2) const
{
	return p1->Compare(p2) < 0;
}

void Book::print()
{
	Publication::print();
	std::cout << author << ' ' << genre << ' ' << binding << std::endl;
	std::cout << "\n---------------------------\n";
}

std::string Book::getBinding()
{
	return binding;
}

void Journal::print()
{
	Publication::print();
	std::cout << ' ' << number << ' ' << year << ' ' << web_site;
	std::cout << "\n--------------------\n";
}