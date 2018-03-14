///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Defines the entry point for the demo application.
///
/// © Sergey Shershakov 2015–2017.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////


//#include "stdafx.h"
//#include "demos.hpp"


// uncomment this if you'd like to get the highest mark
// #define IWANNAGET10POINTS 


#include "src/bidi_linked_list.h"
#include <list>
#include <map>
#include <vector>
#include <iostream>


/** \brief Type alias for a list of integers. */
typedef BidiLinkedList<int> IntBidiLinkedList;


/** \brief Simple list creating. */
void demo1()
{
    IntBidiLinkedList lst;
}

struct A
{
    void foo() {std::cout << "Hi" << std::endl;}
};

struct B
{
    A a;
    A* operator->() {
        return &a;
    }
};


//int _tmain(int argc, _TCHAR* argv[])
int main()
{
    demo1();
    B b;
    b->foo();
    BidiLinkedList<A>::Node* n = new BidiLinkedList<A>::Node(A());
    BidiLinkedList<A>::iterator it(n);
    it->foo();

//    BidiLinkedList<int>::Node* n = new BidiLinkedList<int>::Node();
//    BidiLinkedList<int>::iterator it2(n);
//    BidiLinkedList<int>::iterator it1(n);
//    it1 = it2;
//    swap(it1, it2);
//
////    std::map<int, int>::iterator iterator;
////    iterator->first
//    std::list<char> list;
//    list.push_back('c');
//    std::list<char>::iterator lt = list.begin();
//    char c = *lt;
//
////    lt->getValue


    return 0;
}

