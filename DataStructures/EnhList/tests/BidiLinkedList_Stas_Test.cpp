//
// Created by Stas Don on 21/10/2017.
//


#include <gtest/gtest.h>

// !!! uncomment this if you'd like to get the highest mark !!!
// раскомментируй эту строчку, если хочется получить оценочку повыше
#define IWANNAGET10POINTS

#include "../src/bidi_linked_list.h"

/** \brief Type alias for a list of integers */
typedef BidiLinkedList<int> IntBidiList;
typedef IntBidiList::Node IntBidiListNode;


int getElement(IntBidiList *ls, int index)
{
    if (index < 0 || index >= ls->getSize())
        throw std::out_of_range("Index is out of range");

    IntBidiListNode *ret = ls->getHeadNode();
    for (int i = 0; i < index; i++)
        ret = ret->getNext();
    return ret->getValue();
}

TEST(BidiListInt, swap){
    BidiLinkedList<int> first;
    for (int i = 0; i < 10; i++)
        first.appendEl(i);
    BidiLinkedList<int> second;
    for (int i = 9; i >= 0; i--)
        second.appendEl(i);
    swap(first, second);

    EXPECT_EQ(getElement(&first, 0), 9);
    EXPECT_EQ(getElement(&second, 0), 0);
}

TEST(BidiListInt, copyConstr)
{
    BidiLinkedList<int> first;
    BidiLinkedList<int> empty(first);
    first.appendEl(1);
    BidiLinkedList<int> one_el_list(first);
    EXPECT_EQ(getElement(&first, 0), getElement(&one_el_list, 0));
    EXPECT_EQ(first.getSize(), 1);
    for (int i = 1; i < 10; i++)
        first.appendEl(i);
    BidiLinkedList<int> second(first);
    EXPECT_EQ(first.getSize(), 10);
    EXPECT_EQ(second.getSize(), 10);

    EXPECT_EQ(getElement(&first, 9), getElement(&second, 9));
    EXPECT_EQ(getElement(&first, 0), getElement(&second, 0));

    second.cutFirst(1);

    EXPECT_EQ(getElement(&first, 1), 1);
    EXPECT_EQ(getElement(&second, 1), 2);
}

TEST(BidiListInt, copyOperator)
{
    BidiLinkedList<int> first;
    for (int i = 0; i < 10; i++)
        first.appendEl(i);
    BidiLinkedList<int> second = first;
    EXPECT_EQ(first.getSize(), 10);
    EXPECT_EQ(second.getSize(), 10);


    EXPECT_EQ(getElement(&first, 9), getElement(&second, 9));
    EXPECT_EQ(getElement(&first, 0), getElement(&second, 0));


    second.cutFirst(1);

    EXPECT_EQ(getElement(&first, 1), 1);
    EXPECT_EQ(getElement(&second, 1), 2);
}

TEST(BidiListInt, findLast)
{
    BidiLinkedList<int> lst;
    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode *nd1 = lst.appendEl(10);
    IntBidiListNode *nd2 = lst.appendEl(20);
    IntBidiListNode *nd3 = lst.appendEl(10);
    IntBidiListNode *nd4 = lst.appendEl(22);
    IntBidiListNode *nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

// search empty
    IntBidiListNode *fnd = lst.findLast(nullptr, 10);
    EXPECT_EQ(nullptr, fnd);

// search first
    fnd = lst.findLast(10);
    EXPECT_EQ(nd5, fnd);

// search second from the same node
    fnd = lst.findLast(fnd, 10);
    EXPECT_EQ(nd5, fnd);

// search second from the next node
    fnd = lst.findLast(fnd->getPrev(), 10);
    EXPECT_EQ(nd3, fnd);

// search third from the next node
    fnd = lst.findLast(fnd->getPrev(), 10);
    EXPECT_EQ(nd1, fnd);

// search non-existing fourth
    fnd = lst.findFirst(fnd->getPrev(), 10);
    EXPECT_EQ(nullptr, fnd);
}

TEST(BidiListInt, cutAll2)
{
    IntBidiList lst;

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(10);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(10);
    IntBidiListNode* nd5 = lst.appendEl(10);

    int fndSize = 0;
    IntBidiListNode** fnd = lst.cutAll(10, fndSize);

    EXPECT_EQ(nd1->getNext(), nullptr);
    EXPECT_EQ(nd1->getPrev(), nullptr);
    EXPECT_NE(nullptr, fnd);
    EXPECT_EQ(lst.getSize(), 0);
    EXPECT_EQ(lst.getHeadNode(), nullptr);
    EXPECT_EQ(lst.getLastNode(), nullptr);

    EXPECT_EQ(5, fndSize);
    EXPECT_EQ(nd1, fnd[0]);
    EXPECT_EQ(nd2, fnd[1]);
    EXPECT_EQ(nd3, fnd[2]);
    EXPECT_EQ(nd4, fnd[3]);
    EXPECT_EQ(nd5, fnd[4]);

    delete[] fnd;
}


TEST(BidiListInt, findFirst2)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode *nd1 = lst.appendEl(20);
    IntBidiListNode *nd2 = lst.appendEl(20);
    IntBidiListNode *nd3 = lst.appendEl(20);
    IntBidiListNode *nd4 = lst.appendEl(20);
    IntBidiListNode *nd5 = lst.appendEl(20);

    EXPECT_EQ(5, lst.getSize());
    EXPECT_EQ(nullptr, lst.findFirst(10));
}
TEST(BidiListInt, findAll2)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode *nd1 = lst.appendEl(20);
    IntBidiListNode *nd2 = lst.appendEl(20);
    IntBidiListNode *nd3 = lst.appendEl(20);
    IntBidiListNode *nd4 = lst.appendEl(20);
    IntBidiListNode *nd5 = lst.appendEl(20);

    int fnd_size = 0;
    EXPECT_EQ(5, lst.getSize());
    EXPECT_EQ(nullptr, lst.findAll(10, fnd_size));
    EXPECT_EQ(fnd_size, 0);
}
