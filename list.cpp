#include "list.hpp"

List::List():
first_p{new Element(nullptr, 0, nullptr)}, last_p{new Element(nullptr, 0, nullptr)}
{
  first_p -> next_p = last_p;
  last_p -> prev_p = first_p;
}

List::List(std::initializer_list<int> args): List()
{

    for (auto i : args) insert(i);
}

List::List(List const& rhs): List()
{

    *this = rhs;
}

List::List(List && rhs): List()
{
    *this = std::move(rhs);
}



List::~List ()
{
    erase();
    delete first_p;
    delete last_p;
}

List::Element::Element(Element* p, int d, Element* n):
prev_p {p}, data{d}, next_p{n}
{}

List::Iterator::Iterator(Element* p):
ptr{p}
{}



void List::insert(int const& val) const
{
    Element* p = new Element{first_p, val, first_p->next_p};
    insert_deep(p);
}
void List::insert_deep(Element* const& p) const
{
    if(p->prev_p == last_p->prev_p)
    {
        p->prev_p->next_p = p;
        p->next_p->prev_p = p;
    }
    else
        if (p->data <= p->prev_p->next_p->data)
        {
            p->next_p = p->prev_p->next_p;
            p->prev_p->next_p = p;
            p->next_p->prev_p = p;
        }
        else
        {
            p->prev_p = p->next_p;
            p->next_p = p->next_p->next_p;
            insert_deep(p);
        }
}

void List::print() const
{
    std::cout <<"Listan innehåller: ";
    Element* p = first_p->next_p;
    print_deep(p);
    std::cout << /*std::endl << */ std::endl;
}

void List::print_deep(Element* const& p) const
{
    if (p != last_p)
    {
        std::cout << p->data << " ";
        print_deep(p->next_p);
    }
}

void List::erase() const
{
    while (first_p->next_p!= last_p)
    {
        first_p->next_p = first_p->next_p->next_p;
        delete first_p->next_p->prev_p;
        first_p->next_p->prev_p = first_p;
    }
}

int List::size() const
{
    Element* p = first_p->next_p;
    int count{};
    while (p != last_p)
    {
        count++;
        p = p->next_p;
    }
    return count;
}

int List::index(int const& index) const
{
    if (index < 0)
        throw std::invalid_argument("felaktigt index!");

    Element* p = first_p->next_p;
    for (int i{}; i<index; i++)
    {
        p = p->next_p;
        if (p == last_p)
            throw std::invalid_argument("felaktigt index!");
    }
    return p->data;
}

void List::remove (int const& index) const
{
    if ( index < 0 || index >= size() )
        throw std::invalid_argument("felaktigt index!");
    else
    {
        Element* p = first_p->next_p;
        for (int i{}; i<index; i++)
        {
            p = p->next_p;
        }
        p->next_p->prev_p = p->prev_p;
        p->prev_p->next_p = p->next_p;
        delete p;
    }
}

bool List::operator == (List const& rhs) const
{
    if (size() != rhs.size())
        return false;
    Element* p = new Element (first_p->next_p, 0, rhs.first_p->next_p);
    while (p->prev_p != last_p)
    {
        if (p->prev_p->data != p->next_p->data)
        {
            delete p;
            return false;
        }
        p->prev_p = p->prev_p->next_p;
        p->next_p = p->next_p->next_p;
    }
    delete p;
    return true;
}

List& List::operator = (List const& rhs)
{
    erase();
    Element* p = rhs.first_p->next_p;
    while (p!=rhs.last_p)
    {
        insert(p->data);
        p = p->next_p;
    }
    return *this;
}

List& List::operator = (List && rhs)
{
    erase();
    first_p->next_p = rhs.first_p->next_p;
    last_p->prev_p = rhs.last_p->prev_p;
    rhs.first_p->next_p->prev_p = first_p;
    rhs.last_p->prev_p->next_p = last_p;
    rhs.first_p->next_p = rhs.last_p;
    rhs.last_p->prev_p = rhs.first_p;
    return *this;
}



List::Iterator List::begin()
{
    Iterator iter{first_p->next_p};
    return iter;
}

List::Iterator List::end()
{
  Iterator iter{last_p};
  return iter;
}

List::Iterator & List::Iterator::operator++()
{
    *this = ptr->next_p;
    return *this;
}

bool List::Iterator::operator!=(Iterator const& rhs) const
{
    if (ptr == rhs.ptr)
        return false;
    return true;
}

bool List::Iterator::operator==(Iterator const& rhs) const
{
    if (ptr == rhs.ptr)
        return true;
    return false;
}

int List::Iterator::operator *() const
{
  return ptr->data;
}
