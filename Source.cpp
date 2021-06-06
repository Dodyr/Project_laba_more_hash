#include <iostream>
#include <Windows.h>
#include <vector>

#include "Header1.h"

//функция предполагает, что список публикаций отсортирован по количеству страниц по возрастанию
void destroy_books(Hash_table& table, Sorter& sorter)
{
    IterarotSort i = sorter.begin();
    bool found;
    Publication* p = table.Find((*i), found);
    int min_pages = p->GetNPages();
    while (p->GetNPages() == min_pages && i != sorter.end())
    {
        Book* book = dynamic_cast<Book*>(p);
        if (book && book->getBinding() == "softcover")
        {
            table.Delete(book->getName());
            i = sorter.erase(i);
            p = table.Find((*i), found);
            delete book;
        }
        else
        {
            i++;
            p = table.Find((*i), found);
        }
    }
}

void sort_(Sorter& sorter, Hash_table& table)
{
    auto cmp = [&table](std::string a, std::string b)->bool {
        bool founda, foundb;
        Publication* pa = table.Find(a, founda);
        Publication* pb = table.Find(b, foundb);
        // make sure that pa abn pb found and not NULL
        return pa->GetNPages() < pb->GetNPages(); 
    };
    sorter.sort(cmp);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    std::ifstream fin("lbr.txt");
    if (fin.is_open())
    {
        Hash_table table;
        Sorter sorter = Hash_full(fin, table);
        sort_(sorter, table);
        destroy_books(table, sorter);
        print_(sorter, table);
    }
    fin.close();
    return 0;
}