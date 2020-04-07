#ifndef List_h
#define List_h
#include <initializer_list>
#include <memory>
#include <iterator>
#include <iostream>


class List
{
public:
    

    
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
    void print() const;
    
    
    
private:
    struct Node;
    std::unique_ptr<Node> head;
    Node * tail;
    int sz;
    struct Node
    {
        Node() = default;
        Node(int v, Node* p, std::unique_ptr<Node> n):
        value{v}, prev{p}, next{std::move(n)}
        {}
        
        int value;
        Node * prev;
        std::unique_ptr<Node> next;
    };
    
private:

    class Iterator    //Fattar inte om Iterator-classen ska vara i List-klassen eller utanför
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;      //Vad ska jag ha det här till?
        typedef int value_type;             // Ska de vara int eller Node*?     int
        typedef int difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        friend class List;
    private:
        Iterator();
        Iterator(Node*);
        Node* ptr;

    public:
        Iterator & operator ++();
        Iterator operator ++(int const);
        Iterator & operator --();
        Iterator operator --(int const);
        int operator *() const;
        bool operator ==(Iterator const&) const;
        bool operator !=(Iterator const&) const;
        
    };
public:
    Iterator begin();
    Iterator end();
    
};







#endif
