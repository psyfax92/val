#ifndef list_hpp
#define list_hpp
#include <iostream>
#include <initializer_list>

class List
{
private:
    class Element
    {
    public:
        Element (Element*, int, Element*);
        Element* prev_p;
        int data;
        Element* next_p;
    };
    
public:
    class Iterator
    {
    public:
        Iterator(Element*);
        Iterator & operator++();
        bool operator==(Iterator const&) const;
        bool operator!=(Iterator const&) const;
        int operator *() const;
    private:
        Element* ptr;
    };

private:
    
    Element* first_p;
    Element* last_p;

    void init_sentinels() &;
    void insert_deep(Element* const&) const;
    void print_deep(Element* const&) const;

public:

    List();
    List(std::initializer_list<int> a_args);
    List(List const&);
    List(List &&);
    ~List();

    void insert(int const&) const;
    void print() const;
    void erase() const;
    int size() const;
    int index(int const&) const;
    void remove (int const&) const;
    bool operator == (List const&) const;

    List& operator = (List const&);
    List& operator = (List &&);

    Iterator begin();
    Iterator end();

};
#endif
