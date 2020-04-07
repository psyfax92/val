#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>

//eraesa bara att sätta p=nullptr;



List::List():
head{ new Node{} }, tail{}, sz{}
{
    Node* pre{head.get()};
    std::unique_ptr<Node> p = std::make_unique<Node>(0, pre, nullptr);
    head->next = std::move(p);
    tail = (head->next).get();
}

List::List(List const & other):
List{}
{
    for (Node * tmp {(other.head->next).get()}; tmp != other.tail ; )
    {
        push_back(tmp->value);
        tmp = (tmp->next).get();
    }
}
List::List(List && tmp) noexcept:
List{}
{
    swap(tmp);
}
List::List(std::initializer_list<int> lst):
List{}
{
    for ( auto val : lst )
    {
        push_back(val);
    }
}


void List::push_front(int value)
{
    Node * old_first {(head->next).get() };
    head->next = std::make_unique<Node> (value, head.get(), std::move(head->next));
    old_first->prev = (head->next).get();
    ++sz;
}
void List::push_back(int value)
{
    tail->prev->next = std::make_unique<Node> (value, tail->prev, std::move(tail->prev->next));
    tail->prev = (tail->prev->next).get();
    ++sz;
}

bool List::empty() const noexcept
{
    return (head->next).get() == tail;
}

int List::back() const noexcept
{
    return tail->prev->value;
}
int & List::back() noexcept
{
    return tail->prev->value;
}

int List::front() const noexcept
{
    return head->next->value;
}
int & List::front() noexcept
{
    return head->next->value;
}

int & List::at(int idx)
{
    return const_cast <int &> ( static_cast<List const *>(this) -> at(idx));
}
int const & List::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{"Index not found"};
    Node * tmp = (head->next).get();
    while ( idx > 0 )
    {
        tmp = (tmp->next).get();
        --idx;
    }
    return tmp->value;
}

int List::size() const noexcept
{
    return sz;
}

void List::swap(List & other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}

List & List::operator=(List const & rhs) &
{
    List{rhs}.swap(*this);
    return *this;
}

List & List::operator=(List && rhs)& noexcept
{
    swap(rhs);
    return *this;
}

void List::print() const
{
    Node* p {(head->next).get()};
    while (p != tail)
    {
        std::cout<<p->value<<' ';
        p = p->next.get();
    }
    std::cout<<std::endl;
}






List::Iterator::Iterator():
ptr{nullptr}
{}

List::Iterator::Iterator(Node* p):
ptr{p}
{}

List::Iterator List::begin()
{
    Iterator tmp {(head->next).get()};
    return tmp;
}
List::Iterator List::end()
{
    Iterator tmp {tail};
    return tmp;
}

List::Iterator & List::Iterator::operator ++()
{
    ptr=(ptr->next).get();
    return *this;
}
List::Iterator List::Iterator::operator ++(int const)
{
    Iterator tmp{*this};
    ++(*this);
    return tmp;
}
List::Iterator & List::Iterator::operator --()
{
    ptr=ptr->prev;
    return *this;
}
List::Iterator List::Iterator::operator --(int const)
{
    Iterator tmp{*this};
    --(*this);
    return tmp;
}

int List::Iterator::operator *() const
{
    return ptr->value;
}

bool List::Iterator::operator ==(Iterator const& rhs) const
{
    if (ptr==rhs.ptr)
        return true;
    else
        return false;
}
bool List::Iterator::operator !=(Iterator const& rhs) const
{
    return !(*this==rhs);
}
