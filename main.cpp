#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "list.hpp"

using namespace std;

TEST_CASE ("check if empty")
{
    List l{};
    CHECK (l == List{});
}

TEST_CASE ("insert and unlimited in parameters")
{
    List l{3,7,-2};
    l.insert(-1);
    CHECK (l == List{-2,7,-1,3});
}
TEST_CASE ("erase whole list")
{
    List l{3,10,-6,7};
    l.erase();
    CHECK (l == List {});
    l.insert(100);
    l.insert(-50);
    l.erase();
    CHECK (l == List {});
}

TEST_CASE ("get size of list")
{
    List l{2,7,-1,0,0};
    CHECK (l.size() == 5);
}

TEST_CASE ("get element data of specific index")
{
    List l{4,5,6,7,};
    CHECK (l.index(0) == 4);
    CHECK (l.index(3) == 7);
    List l2{3,-11,20,-9,};
    CHECK (l2.index(0) == -11);
    CHECK (l2.index(2) == 3);

    SECTION ("Throws as well")
    {
        CHECK_THROWS( l.index(10) );
        CHECK_THROWS( l.index(-33) );
    }
}

TEST_CASE ("remove element fron list")
{
    List l{4,6,8,10,12};
    l.remove(2);
    CHECK (l == List {4,6,10,12});
    l.remove(2);
    CHECK (l == List {4,6,12});

    SECTION ("Throws as well")
    {
        CHECK_THROWS( l.remove(10));
        CHECK_THROWS( l.remove(-4));
    }
}

TEST_CASE ("constructor - (copy)")
{
    List l{3,-3,-3};
    List l2{l};
    CHECK (l == List {-3,3,-3});
    CHECK (l2 == List {-3,3,-3});
}

TEST_CASE ("constructor (move)")
{
    List l{3,-3,-3};
    List l2{move(l)};
    CHECK (l == List {});
    CHECK (l2 == List {-3,3,-3});
}

TEST_CASE ("operator = (copy)")
{
    List l{-3,6,6,-2};
    List l2{7,7,7};
    l2 = l;
    CHECK (l == List {-2,-3,6,6});
    CHECK (l2 == List {-2,-3,6,6});
}

TEST_CASE ("operator = (move)")
{
    List l{-3,6,6,-2};
    List l2{7,7,7};
    l2 = move(l);
    CHECK (l == List {});
    CHECK (l2 == List {-2,-3,6,6});
}


TEST_CASE ("begin and end - auto")
{
    List l{-2,10,-4,20};
    int i{};
    for (List::Iterator it = l.begin(); it != l.end(); ++it)
    {
        cout<< *it << endl;
    }
}

TEST_CASE ("begin and end")
{
    List l{-2,10,-4,20};
    int i{};
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        cout<< *it << endl;
    }
}

#if 0
#endif
