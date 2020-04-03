//#define CATCH_CONFIG_MAIN
#include "List.h"
#include "catch.hpp"

TEST_CASE( "Create list" )
{
    List lst{1,4,2,6,8,9};
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

TEST_CASE( "Create const list" )
{
    const List lst{-2,4,-1};
    CHECK(lst.at(0) == -2);
    CHECK(lst.at(1) == 4);
    CHECK(lst.at(2) == -1);
 
}

TEST_CASE( "Empty" )
{
    List l1 {};
    CHECK(l1.empty());
    l1.push_back(3);
    CHECK_FALSE (l1.empty());
    
}

TEST_CASE( "Push_front & Push_back" )
{
    List l1 {};

    l1.push_front(2);
    CHECK(l1.size() == 1);
    CHECK(l1.at(0) == 2);
    
    l1.push_back(3);
//    CHECK(l1.size() == 2);
//    CHECK(l1.at(0) == 2);
//    CHECK(l1.at(1) == 3);
}

TEST_CASE( "Front & Back" )
{
    List l1 {2,1,4,6,3};
    CHECK(l1.front() == 2);
    CHECK_FALSE(l1.front() == 1);
    CHECK(l1.back() == 3);
    CHECK_FALSE(l1.back() == 6);
    
}


TEST_CASE( "Size" )
{
    List l1 {2,4,-1,0,5};
    CHECK(l1.size() == 5);
}

TEST_CASE( "Swap" )
{
    List l1 {2,4};
    List l2 {8};
    l1.swap(l2);
    CHECK(l1.at(0) == 8);
    CHECK(l1.size() == 1);
    CHECK(l2.at(0) == 2);
    CHECK(l2.at(1) == 4);
}


TEST_CASE( "=" )
{
    List l1 {10};
    List l2 = l1;
    CHECK(l1.at(0) == 10);
    CHECK(l2.at(0) == 10);
    CHECK_FALSE(l1.empty());
    CHECK_FALSE(l2.empty());
    
    List l3 {10};
    List l4 = std::move(l3);
    CHECK(l3.empty());
    CHECK(l4.at(0) == 10);
    CHECK_FALSE(l4.empty());
}
