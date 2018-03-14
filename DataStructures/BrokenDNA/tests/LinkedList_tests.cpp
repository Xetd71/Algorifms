#include <gtest/gtest.h>
#include "../src/linked_list.h"


using namespace xi;

TEST(LinkedList, assert_constructor)
{
    LinkedList<int> list1;
    Node<int>* preHead = list1.getPreHead();

    EXPECT_NE(nullptr, preHead);
    EXPECT_EQ(nullptr, preHead->next);
}


TEST(LinkedList, assert_constructorCopy)
{
    int length = 5;
    LinkedList<int> list1;
    for(int i = 0; i < length; i++)
        list1.addElementToEnd(i);

    LinkedList<int> list2(list1);

    Node<int>* list1Current = list1.getPreHead();
    Node<int>* list2Current = list2.getPreHead();
    EXPECT_NE(list1Current, list2Current);

    for(int i = 0; i < length; i++)
    {
        EXPECT_EQ(i, list2[i]);

        list1Current = list1Current->next;
        list2Current = list2Current->next;
        EXPECT_NE(list1Current, list2Current);
    }
}

TEST(LinkedList, assert_asignmentOperator)
{
    int length = 5;
    int k;
    LinkedList<int> list1;
    LinkedList<int> list2;
    for(int i = 0; i < length; i++) {
        list1.addElementToEnd(i);
        k = i * i;
        list2.addElementToEnd(k);
    }

    list1 = list2;

    Node<int>* list1Current = list1.getPreHead();
    Node<int>* list2Current = list2.getPreHead();
    EXPECT_NE(list1Current, list2Current);

    for(int i = 0; i < length; i++) {
        EXPECT_EQ(i * i, list1[i]);

        list1Current = list1Current->next;
        list2Current = list2Current->next;
        EXPECT_NE(list1Current, list2Current);
    }
}


TEST(LinkedList, assert_indexOperator)
{
    int length = 5;
    LinkedList<int> list;
    for(int i = 0; i < length; i++)
        list.addElementToEnd(i);

    for(int i = 0; i < length - 2; i++)
        EXPECT_EQ(i, list[i]);

    list[3] = 10;
    list[4] = -5;

    EXPECT_EQ(10, list[3]);
    EXPECT_EQ(-5, list[4]);

    EXPECT_THROW(list[5], std::out_of_range);
}


TEST(LinkedList, assert_size)
{
    int length = 5;
    LinkedList<int> list;
    for(int i = 0; i < length; i++)
        list.addElementToEnd(i);

    EXPECT_EQ(5, list.size());

    list.deleteNextNode(list.getPreHead()->next);
    EXPECT_EQ(4, list.size());
}


TEST(LinkedList, assert_addElementsToEnd)
{
    int length = 5;
    int a;
    LinkedList<int> list;

    a = 3;
    list.addElementToEnd(a);

    EXPECT_EQ(3, list.getPreHead()->next->value);
}


TEST(LinkedList, assert_deleteNode)
{
    int length = 3;
    LinkedList<int> list;
    for(int i = 0; i < length; i++)
        list.addElementToEnd(i);

    list.deleteNextNode(list.getPreHead()->next);

    EXPECT_EQ(length - 1, list.size());
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(2, list[1]);
    EXPECT_THROW(list[2], std::out_of_range);
}


TEST(LinkedList, assert_deleteNodes)
{
    int length = 3;
    LinkedList<int> list;
    for(int i = 0; i < length; i++)
        list.addElementToEnd(i);

    list.deleteNodes(list.getPreHead(), list.getPreHead()->next->next);

    EXPECT_EQ(1, list.size());
    EXPECT_EQ(2, list.getPreHead()->next->value);
}


TEST(LinkedList, assert_moveNodeAfter)
{
    int length = 3;
    int k;
    LinkedList<int> list1;
    LinkedList<int> list2;
    for(int i = 0; i < length; i++)
    {
        list1.addElementToEnd(i);
        k = i * i;
        list2.addElementToEnd(k);
    }

    list1.moveNodeAfter(list1.getPreHead(), list2.getPreHead()->next->next);

    EXPECT_EQ(4, list1.size());
    EXPECT_EQ(2, list2.size());
    EXPECT_EQ(4, list1[0]);
}


TEST(LinkedList, assert_moveNodesAfter)
{
    int length = 3;
    int k;
    LinkedList<int> list1;
    LinkedList<int> list2;
    for(int i = 0; i < length; i++) {
        list1.addElementToEnd(i);
        k = i * i;
        list2.addElementToEnd(k);
    }

    list1.moveNodesAfter(list1.getPreHead(), list2.getPreHead(), list2.getPreHead()->next->next);

    EXPECT_EQ(5, list1.size());
    EXPECT_EQ(1, list2.size());
    EXPECT_EQ(4, list2[0]);
}


TEST(LinkedList, assert_moveNodeToEnd)
{
    int length = 3;
    int k;
    LinkedList<int> list1;
    LinkedList<int> list2;
    for(int i = 0; i < length; i++) {
        list1.addElementToEnd(i);
        k = i * i;
        list2.addElementToEnd(k);
    }

    list1.moveNodeToEnd(list2.getPreHead()->next->next);

    EXPECT_EQ(4, list1.size());
    EXPECT_EQ(2, list2.size());
    EXPECT_EQ(4, list1.getLastNode()->value);
}


TEST(LinkedList, assert_moveNodesToEnd)
{
    int length = 3;
    int k;
    LinkedList<int> list1;
    LinkedList<int> list2;
    for(int i = 0; i < length; i++) {
        list1.addElementToEnd(i);
        k = i * i;
        list2.addElementToEnd(k);
    }

    list1.moveNodesToEnd(list2.getPreHead(), list2.getPreHead()->next->next);

    EXPECT_EQ(5, list1.size());
    EXPECT_EQ(1, list2.size());
    EXPECT_EQ(4, list2.getLastNode()->value);
}