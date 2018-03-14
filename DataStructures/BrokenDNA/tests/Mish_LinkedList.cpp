#include <gtest/gtest.h>
#include "../src/linked_list.h"

TEST(Linked_List, simplest)
{
    using namespace xi;

    LinkedList<int> linkedList;
}


TEST(Linked_List, DefConstructor)
{
    using namespace xi;

    LinkedList<int> linkedList;
    EXPECT_EQ(linkedList.getPreHead()->next, nullptr);
    EXPECT_EQ(linkedList.size(), 0);
}

TEST(Linked_List, CopyConstructor)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();
    list.getPreHead()->next = new Node<int>();
    list.getPreHead()->next->value = 10;

    LinkedList<int> linkedList(list);

    EXPECT_NE(linkedList.getPreHead()->next, nullptr);
    EXPECT_NE(linkedList.getPreHead(), list.getPreHead());
    EXPECT_EQ(linkedList.size(), 1);
    EXPECT_EQ(linkedList.getPreHead()->next->value, 10);
}

TEST(Linked_List, GetPrehead)
{
    using namespace xi;

    LinkedList<int> linkedList;

    EXPECT_NE(linkedList.getPreHead(), nullptr);
}

TEST(Linked_List, IndexOper)
{
    using namespace xi;

    LinkedList<int> list;
    list.getPreHead()->next = new Node<int>();
    list.getPreHead()->next->value = 1;
    list.getPreHead()->next->next = new Node<int>();
    list.getPreHead()->next->next->value = 2;
    EXPECT_NE(list.getPreHead()->next, nullptr);
    EXPECT_EQ(list.size(), 2);

    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);

    // out of range
    EXPECT_THROW(list[2] = 3, std::out_of_range);
}

TEST(Linked_List, GetSize)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();

    EXPECT_EQ(list.size(), 0);

    list.getPreHead()->next = new Node<int>();
    list.getPreHead()->next->value = 10;

    EXPECT_EQ(list.size(), 1);

    list.getPreHead()->next->next = new Node<int>();
    list.getPreHead()->next->next->value = 10;

    EXPECT_EQ(list.size(), 2);
}

TEST(Linked_List, AddElemToEnd)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();

    int a = 1;
    list.addElementToEnd(a);

    EXPECT_NE(list.getPreHead()->next, nullptr);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 1);

    a = 2;

    EXPECT_NE(list.getPreHead()->next, nullptr);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 1);

    list.addElementToEnd(a);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_THROW(list[2], std::out_of_range);
}

TEST(Linked_List, DeleteNode)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);

    list.deleteNextNode(list.getPreHead());

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 2);

    list.deleteNextNode(list.getPreHead()->next);

    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 2);

    list.deleteNextNode(list.getPreHead());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.getPreHead()->next, nullptr);

    EXPECT_THROW(list.deleteNextNode(list.getPreHead()), std::logic_error);
}

TEST(Linked_List, DeleteNodes)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);
    list.addElementToEnd(d);
    list.addElementToEnd(e);

    list.deleteNodes(list.getPreHead(), list.getPreHead()->next->next);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 3);

    list.deleteNodes(list.getPreHead(), list.getPreHead()->next);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 4);

    list.deleteNodes(list.getPreHead(), list.getPreHead()->next->next);

    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.getPreHead()->next, nullptr);
    EXPECT_THROW(list.deleteNextNode(list.getPreHead()), std::logic_error);
}

TEST(Linked_List, MoveNodeToEnd)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();
    LinkedList<int> list1 = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);
    list1.addElementToEnd(d);
    list1.addElementToEnd(e);

    list.moveNodeToEnd(list1.getPreHead()->next);

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list[3], 5);
    EXPECT_EQ(list1[0], 4);

    list.moveNodeToEnd(list1.getPreHead());

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list[4], 4);
    EXPECT_THROW(list.moveNodeToEnd(list1.getPreHead()), std::logic_error);

    list1.moveNodeToEnd(list.getPreHead());

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list1[0], 1);
}

TEST(Linked_List, MoveNodesToEnd)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();
    LinkedList<int> list1 = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);
    list1.addElementToEnd(d);
    list1.addElementToEnd(e);

    list.moveNodesToEnd(list1.getPreHead(), list1.getPreHead()->next->next);

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list[4], 5);
    EXPECT_THROW(list.moveNodesToEnd(list1.getPreHead(), list1.getPreHead()->next), std::logic_error);

    list1.moveNodesToEnd(list.getPreHead(), list.getPreHead()->next->next);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list[0], 3);
    EXPECT_EQ(list1[0], 1);
}

TEST(Linked_List, MoveNodeAfter)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();
    LinkedList<int> list1 = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);
    list1.addElementToEnd(d);
    list1.addElementToEnd(e);

    list.moveNodeAfter(list.getPreHead(), list1.getPreHead()->next);

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list[0], 5);
    EXPECT_EQ(list1[0], 4);

    list.moveNodeAfter(list.getPreHead()->next, list1.getPreHead());

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list[1], 4);
    EXPECT_THROW(list.moveNodeAfter(list.getPreHead(), list1.getPreHead()), std::logic_error);

}

TEST(Linked_List, MoveNodesAfter)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();
    LinkedList<int> list1 = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);
    list1.addElementToEnd(d);
    list1.addElementToEnd(e);
    list1.addElementToEnd(f);

    list.moveNodesAfter(list.getPreHead(), list1.getPreHead(), list1.getPreHead()->next->next);

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list1.size(), 1);
    EXPECT_EQ(list[0], 4);
    EXPECT_EQ(list1[0], 6);

    list.moveNodesAfter(list.getPreHead()->next, list1.getPreHead(), list1.getPreHead()->next);

    EXPECT_EQ(list.size(), 6);
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list[1], 6);

}

TEST(Linked_List, CopyOper)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();
    LinkedList<int> list1 = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);
    list1.addElementToEnd(d);
    list1.addElementToEnd(e);

    list1 = list;

    EXPECT_NE(list.getPreHead(), list1.getPreHead());
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], list1[0]);
    EXPECT_EQ(list[1], list1[1]);
    EXPECT_EQ(list[2], list1[2]);

    list.getPreHead()->next->value = 10;

    EXPECT_EQ(list[0], 10);
    EXPECT_NE(list1[0], list[0]);

}

TEST(Linked_List, SwapMethod)
{
    using namespace xi;

    LinkedList<int> list = LinkedList<int>();
    LinkedList<int> list1 = LinkedList<int>();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    list.addElementToEnd(a);
    list.addElementToEnd(b);
    list.addElementToEnd(c);
    list1.addElementToEnd(d);
    list1.addElementToEnd(e);

    std::swap(list1, list);

    EXPECT_NE(list.getPreHead(), list1.getPreHead());
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 4);
    EXPECT_EQ(list1[0], 1);

    list.getPreHead()->next->value = 10;

    EXPECT_EQ(list[0], 10);
    EXPECT_NE(list1[0], list[0]);

}