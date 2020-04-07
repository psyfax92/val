#ifndef List_h
#define List_h
#include <initializer_list>
#include <memory>
#include <iterator>
#include <iostream>


class List
{
public:
    
    typedef std::bidirectional_iterator_tag iterator_category;      //Vad ska jag ha det här till?
    typedef int value_type;             // Ska de vara int eller Node*?     int
    typedef int difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    List();
    ~List() = default;
    List(List const &);
    List(List &&) noexcept;
    List(std::initializer_list<int>);
    
    List & operator=(List const &)&;
    List & operator=(List &&)& noexcept;
    
    void push_front(int);
    void push_back(int);
    
    int back() const noexcept;
    int & back() noexcept;
    
    int front() const noexcept;
    int & front() noexcept;
    
    int & at(int idx);
    int const & at(int idx) const;
    
    int size() const noexcept;
    bool empty() const noexcept;
    
    void swap(List & other) noexcept;
    
private:
    struct Node;
    std::unique_ptr<Node> head;
    Node * tail;
    int sz;
    struct Node
    {
        Node() = default;
        Node(int v, Node* p, Node* n):
        value{v}, prev{p}, next{n}
        {}
        
        int value;
        Node * prev;
        std::unique_ptr<Node> next;
    };

public:

    class Iterator    //Fattar inte om Iterator-classen ska vara i List-klassen eller utanför
    {
    public:
        Iterator();
        Iterator(Node*);
//        iterator_category ic;
//        value_type v;
//        difference_type d;
//        pointer p;
//        reference r;
        
        Iterator & operator ++();
        Iterator operator ++(int const);
        int operator *() const;
        
    //private:
        Node* ptr;
        
    };

    Iterator begin();
    Iterator end();
    
};


 




#endif
