#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>


// fråga hur gör man för att struct delen ska va i cc filen?


List::List():
head{ new Node{} }, tail{}, sz{}
{
    Node* pre{head.get()};
    std::unique_ptr<Node> p{new Node{0, pre, nullptr}};
    head->next = std::move(p);
    tail = (head->next).get();
}

List::List(List const & other):
List{}
{
    for (Node * tmp {(other.head->next).get()}; tmp != other.tail ; )
    {
        push_back(tmp->value);
        tmp = (tmp->next).get();    //osäker om funkar
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
    Node* pre{head.get()};
    std::unique_ptr<Node> old_first { new Node{value, pre, nullptr}};
    old_first->next = std::move(head->next);
    old_first->next->prev = old_first.get();
    old_first = std::move(head->next);
    ++sz;
}
void List::push_back(int value)
{
    std::unique_ptr<Node> old_last { new Node {value, tail->prev, nullptr} };
    old_last->next = std::move(old_last->prev->next);
    tail->prev=old_last.get();
    old_last->prev->next = std::move(old_last);
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
