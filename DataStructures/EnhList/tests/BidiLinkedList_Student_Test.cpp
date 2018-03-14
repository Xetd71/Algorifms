#include <gtest/gtest.h>
#include "../src/bidi_linked_list.h"

typedef BidiLinkedList<int> IntBidiList;
typedef IntBidiList::Node IntBidiListNode;

TEST(BidiLinkedList_myTests, simpleTest)
{
    IntBidiList list;

    EXPECT_EQ(nullptr, list.getHeadNode());
    EXPECT_EQ(nullptr, list.getLastNode());
    EXPECT_EQ(0, list.getSize());
}


TEST(BidiLinkedList_myTests, copyConstructor)
{
    size_t len = 5;
    IntBidiList list;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    IntBidiList list1 = list;


    EXPECT_NE(list.getHeadNode(), list1.getHeadNode());
    EXPECT_NE(list.getLastNode(), list1.getLastNode());

    EXPECT_EQ(list.getSize(), list1.getSize());
    EXPECT_EQ(len, list1.getSize());

    IntBidiListNode* cNodeList = list.getHeadNode();
    IntBidiListNode* cNodeList1 = list1.getHeadNode();
    for(int i = 0; i < len; ++i) {
        EXPECT_EQ(i, cNodeList1->getValue());
        EXPECT_NE(cNodeList,cNodeList1);
        cNodeList1 = cNodeList1->getNext();
        cNodeList = cNodeList->getNext();
    }
}


TEST(BidiLinkedList_myTests, asingmentOperator)
{
    size_t len = 5;
    IntBidiList list, list1;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    list1 = list;


    EXPECT_NE(list.getHeadNode(), list1.getHeadNode());
    EXPECT_NE(list.getLastNode(), list1.getLastNode());

    EXPECT_EQ(list.getSize(), list1.getSize());
    EXPECT_EQ(len, list1.getSize());

    IntBidiListNode* cNodeList = list.getHeadNode();
    IntBidiListNode* cNodeList1 = list1.getHeadNode();
    for(int i = 0; i < len; ++i) {
        EXPECT_EQ(i, cNodeList1->getValue());
        EXPECT_NE(cNodeList,cNodeList1);

        cNodeList1 = cNodeList1->getNext();
        cNodeList = cNodeList->getNext();
    }
}


TEST(BidiLinkedList_myTests, swapMethod)
{
    size_t len = 5;
    IntBidiList list, list1;
    list.appendEl(0);
    for(int i = 1; i < len; ++i){
        list.appendEl(i);
        list1.appendEl(i * len);
    }
    swap(list, list1);


    IntBidiListNode* cNodeList = list.getHeadNode();
    IntBidiListNode* cNodeList1 = list1.getHeadNode();

    EXPECT_EQ(0, cNodeList1->getValue());
    cNodeList1 = cNodeList1->getNext();

    for(int i = 1; i < len; ++i) {
        EXPECT_EQ(i, cNodeList1->getValue());
        EXPECT_EQ(i * len, cNodeList->getValue());

        cNodeList1 = cNodeList1->getNext();
        cNodeList = cNodeList->getNext();
    }
}


TEST(BidiLinkedList_myTests, clear)
{
    size_t len = 3;
    IntBidiList list;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    list.clear();


    EXPECT_EQ(nullptr, list.getHeadNode());
    EXPECT_EQ(nullptr, list.getLastNode());
    EXPECT_EQ(0, list.getSize());
}


TEST(BidiLinkedList_myTests, appeneElement)
{
    IntBidiList list;

    IntBidiListNode* el1 = list.appendEl(12);

    EXPECT_EQ(el1, list.getHeadNode());
    EXPECT_EQ(12, list.getHeadNode()->getValue());
    EXPECT_EQ(el1, list.getLastNode());
    EXPECT_EQ(1, list.getSize());

    EXPECT_EQ(nullptr, el1->getPrev());
    EXPECT_EQ(nullptr, el1->getNext());


    IntBidiListNode* el2 = list.appendEl(5);

    EXPECT_EQ(el1, list.getHeadNode());
    EXPECT_EQ(el2, list.getLastNode());
    EXPECT_EQ(5, list.getLastNode()->getValue());
    EXPECT_EQ(2, list.getSize());

    EXPECT_EQ(nullptr, el1->getPrev());
    EXPECT_EQ(el2, el1->getNext());
    EXPECT_EQ(el1, el2->getPrev());
    EXPECT_EQ(nullptr, el2->getNext());


    IntBidiListNode* el3 = list.appendEl(10);

    EXPECT_EQ(el1, list.getHeadNode());
    EXPECT_EQ(el3, list.getLastNode());
    EXPECT_EQ(10, list.getLastNode()->getValue());
    EXPECT_EQ(3, list.getSize());

    EXPECT_EQ(nullptr, el1->getPrev());
    EXPECT_EQ(el2, el1->getNext());
    EXPECT_EQ(el1, el2->getPrev());
    EXPECT_EQ(el3, el2->getNext());
    EXPECT_EQ(el2, el3->getPrev());
    EXPECT_EQ(nullptr, el3->getNext());
}


TEST(BidiLinkedList_myTests, findFirst_findFirstFrom)
{
    IntBidiList list;
    list.appendEl(2);
    IntBidiListNode* el1 = list.appendEl(1);
    IntBidiListNode* el2 = list.appendEl(1);
    list.appendEl(3);
    IntBidiListNode* el3 = list.appendEl(1);
    IntBidiListNode* el4 = list.appendEl(4);

    EXPECT_EQ(el1, list.findFirst(1));
    EXPECT_EQ(el1, list.findFirst(el1, 1));
    EXPECT_EQ(el3, list.findFirst(el3, 1));
    EXPECT_EQ(nullptr, list.findFirst(el4, 1));
    EXPECT_EQ(nullptr, list.findFirst(nullptr, 1));
}


TEST(BidiLinkedList_myTests, findLast_findLastFrom)
{
    IntBidiList list;
    IntBidiListNode* el = list.appendEl(2);
    IntBidiListNode* el1 = list.appendEl(1);
    IntBidiListNode* el2 = list.appendEl(1);
    list.appendEl(3);
    IntBidiListNode* el3 = list.appendEl(1);
    IntBidiListNode* el4 = list.appendEl(4);

    EXPECT_EQ(el3, list.findLast(1));
    EXPECT_EQ(el1, list.findLast(el1, 1));
    EXPECT_EQ(el3, list.findLast(el3, 1));
    EXPECT_EQ(nullptr, list.findLast(el, 1));
    EXPECT_EQ(nullptr, list.findLast(nullptr, 1));
}


TEST(BidiLinkedList_myTests, findAll)
{
    IntBidiList list;
    IntBidiListNode* el = list.appendEl(2);
    IntBidiListNode* el1 = list.appendEl(1);
    IntBidiListNode* el2 = list.appendEl(1);
    list.appendEl(3);
    IntBidiListNode* el3 = list.appendEl(1);
    IntBidiListNode* el4 = list.appendEl(4);

    int size;
    IntBidiListNode** foundObj = list.findAll(1, size);
    EXPECT_EQ(3, size);
    EXPECT_EQ(el1, foundObj[0]);
    EXPECT_EQ(el2, foundObj[1]);
    EXPECT_EQ(el3, foundObj[2]);
    delete[] foundObj;


    foundObj = list.findAll(el2, 1, size);
    EXPECT_EQ(2, size);
    EXPECT_EQ(el2, foundObj[0]);
    EXPECT_EQ(el3, foundObj[1]);
    delete[] foundObj;


    foundObj = list.findAll(el4, 1, size);
    EXPECT_EQ(0, size);
    delete[] foundObj;
}


TEST(BidiLinkedList_myTests, cutNode)
{
    IntBidiList list;
    IntBidiListNode* el1 = list.appendEl(1);
    IntBidiListNode* el2 = list.appendEl(2);
    IntBidiListNode* el3 = list.appendEl(3);
    IntBidiListNode* el4 = list.appendEl(4);
    IntBidiListNode* el5 = list.appendEl(5);
    IntBidiListNode* el6 = list.appendEl(6);


    // cut head
    EXPECT_EQ(el1, list.cutNode(el1));
    EXPECT_EQ(5, list.getSize());

    EXPECT_EQ(el2, list.getHeadNode());
    EXPECT_EQ(el6, list.getLastNode());

    EXPECT_EQ(nullptr, el1->getNext());
    EXPECT_EQ(nullptr, el1->getPrev());
    EXPECT_EQ(el3, el2->getNext());
    EXPECT_EQ(el2, el3->getPrev());


    // cut in center
    EXPECT_EQ(el4, list.cutNode(el4));
    EXPECT_EQ(4, list.getSize());

    EXPECT_EQ(el2, list.getHeadNode());
    EXPECT_EQ(el6, list.getLastNode());

    EXPECT_EQ(nullptr, el4->getNext());
    EXPECT_EQ(nullptr, el4->getPrev());
    EXPECT_EQ(el5, el3->getNext());
    EXPECT_EQ(el3, el5->getPrev());


    // cut tail
    EXPECT_EQ(el6, list.cutNode(el6));
    EXPECT_EQ(3, list.getSize());

    EXPECT_EQ(el2, list.getHeadNode());
    EXPECT_EQ(el5, list.getLastNode());

    EXPECT_EQ(nullptr, el6->getNext());
    EXPECT_EQ(nullptr, el6->getPrev());
    EXPECT_EQ(nullptr, el5->getNext());

    // cut nullptr
    EXPECT_THROW(list.cutNode(nullptr), std::invalid_argument);
}


TEST(BidiLinkedList_myTests, cutNodes)
{
    IntBidiList list;
    IntBidiListNode* el1 = list.appendEl(1);
    IntBidiListNode* el2 = list.appendEl(2);
    IntBidiListNode* el3 = list.appendEl(3);
    IntBidiListNode* el4 = list.appendEl(4);
    IntBidiListNode* el5 = list.appendEl(5);
    IntBidiListNode* el6 = list.appendEl(6);
    IntBidiListNode* el7 = list.appendEl(7);
    IntBidiListNode* el8 = list.appendEl(8);


    // cut at center
    list.cutNodes(el2, el4);
    EXPECT_EQ(5, list.getSize());

    EXPECT_EQ(el1, list.getHeadNode());
    EXPECT_EQ(el8, list.getLastNode());

    EXPECT_EQ(nullptr, el2->getPrev());
    EXPECT_EQ(nullptr, el4->getNext());
    EXPECT_EQ(el5, el1->getNext());
    EXPECT_EQ(el1, el5->getPrev());


    // cut with head
    list.cutNodes(el1, el5);
    EXPECT_EQ(3, list.getSize());

    EXPECT_EQ(el6, list.getHeadNode());
    EXPECT_EQ(el8, list.getLastNode());

    EXPECT_EQ(nullptr, el1->getPrev());
    EXPECT_EQ(nullptr, el5->getNext());
    EXPECT_EQ(el7, el6->getNext());
    EXPECT_EQ(nullptr, el6->getPrev());


    // cut with head
    list.cutNodes(el7, el8);
    EXPECT_EQ(1, list.getSize());

    EXPECT_EQ(el6, list.getHeadNode());
    EXPECT_EQ(el6, list.getLastNode());

    EXPECT_EQ(nullptr, el7->getPrev());
    EXPECT_EQ(nullptr, el8->getNext());
    EXPECT_EQ(nullptr, el6->getNext());
    EXPECT_EQ(nullptr, el6->getPrev());


    // cut nullptr
    EXPECT_THROW(list.cutNodes(nullptr, el6), std::invalid_argument);
    EXPECT_EQ(1, list.getSize());
    EXPECT_THROW(list.cutNodes(el6, nullptr), std::invalid_argument);
    EXPECT_EQ(1, list.getSize());
}


TEST(BidiLinkedList_myTests, cutAll)
{
    IntBidiList list;
    IntBidiListNode* el1 = list.appendEl(2);
    IntBidiListNode* el2 = list.appendEl(1);
    IntBidiListNode* el3 = list.appendEl(1);
    IntBidiListNode* el4 = list.appendEl(3);
    IntBidiListNode* el5 = list.appendEl(1);
    IntBidiListNode* el6 = list.appendEl(4);

    int size;
    IntBidiListNode** cutObj = list.cutAll(1, size);
    EXPECT_EQ(3, size);
    EXPECT_EQ(3, list.getSize());

    EXPECT_EQ(el1, list.getHeadNode());
    EXPECT_EQ(el6, list.getLastNode());

    EXPECT_EQ(el4, el1->getNext());
    EXPECT_EQ(el1, el4->getPrev());
    EXPECT_EQ(el6, el4->getNext());
    EXPECT_EQ(el4, el6->getPrev());

    EXPECT_EQ(el2, cutObj[0]);
    EXPECT_EQ(el3, cutObj[1]);
    EXPECT_EQ(el5, cutObj[2]);

    delete[] cutObj;
}