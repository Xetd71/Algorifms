#include <gtest/gtest.h>
#include "../src/bidi_linked_list.h"

typedef BidiLinkedList<int> IntBidiList;
typedef IntBidiList::Node IntBidiListNode;
typedef IntBidiList::iterator IntBidiListIterator;


TEST(BidiLinkedListIterator_myTests, dereferenceOperator)
{
    IntBidiListNode* node = new IntBidiListNode(1);
    IntBidiListIterator it(node);

    EXPECT_EQ(1, *it);

    it++;
    EXPECT_THROW(*it, std::invalid_argument);
}


class A
{
public:
    int getOne()
    {
        return 1;
    }
};

TEST(BidiLinkedListIterator_myTests, arrowOperator)
{
    BidiLinkedList<A>::Node* n = new BidiLinkedList<A>::Node(A());
    BidiLinkedList<A>::iterator it(n);

    EXPECT_EQ(1, it->getOne());

    it++;
    EXPECT_THROW(it->getOne(), std::invalid_argument);
}


TEST(BidiLinkedListIterator_myTests, copyConstructor)
{
    size_t len = 2;
    IntBidiList list;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    IntBidiListIterator it1 = list.begin();
    IntBidiListIterator it2 = list.begin();

    EXPECT_EQ(list.begin(), it1);
    EXPECT_EQ(it1, it2);

    it1++;
    EXPECT_NE(it1, it2);

    it2++;
    EXPECT_EQ(it1, it2);
}


TEST(BidiLinkedListIterator_myTests, assignmentOperation)
{
    size_t len = 2;
    IntBidiList list;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    IntBidiListIterator it1 = list.begin();
    IntBidiListIterator it2 = list.end();
    EXPECT_NE(it1, it2);

    it2 = it1;
    EXPECT_EQ(it1, it2);

    it1++;
    EXPECT_NE(it1, it2);

    it2++;
    EXPECT_EQ(it1, it2);
}


TEST(BidiLinkedListIterator_myTests, pp_postfix_and_prefix)
{
    size_t len = 5;
    IntBidiList list;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    // prefix ++
    int k = 0;
    for(IntBidiListIterator it = list.begin(); it != list.end(); ++it, k++)
        EXPECT_EQ(k, *it);

    // postfix ++
    k = 0;
    for(IntBidiListIterator it = list.begin(); it != list.end(); it++, k++)
        EXPECT_EQ(k, *it);

    // postfix and prefix ++
    IntBidiListIterator it1 = list.begin();
    IntBidiListIterator it2 = list.begin();
    EXPECT_EQ(it1, it2++);
    EXPECT_EQ(++it1, it2);
    EXPECT_EQ(it1, it2);


    it1 = ++list.end();
    EXPECT_THROW(it1++, std::invalid_argument);
    EXPECT_THROW(++it1, std::invalid_argument);
}


TEST(BidiLinkedListIterator_myTests, mm_postfix_and_prefix)
{
    size_t len = 5;
    IntBidiList list;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    // prefix --
    int k = len - 1;
    for(IntBidiListIterator it = list.end(); it != list.begin(); --it, k--)
        EXPECT_EQ(k, *it);

    // postfix --
    k = len - 1;
    for(IntBidiListIterator it = list.end(); it != list.begin(); it--, k--)
        EXPECT_EQ(k, *it);

    // postfix and prefix --
    IntBidiListIterator it1 = list.end();
    IntBidiListIterator it2 = list.end();
    EXPECT_EQ(it1, it2--);
    EXPECT_EQ(--it1, it2);
    EXPECT_EQ(it1, it2);


    it1 = --list.begin();
    EXPECT_THROW(it1--, std::invalid_argument);
    EXPECT_THROW(--it1, std::invalid_argument);
}


TEST(BidiLinkedListIterator_myTests, equals_and_unequals)
{
    size_t len = 2;
    IntBidiList list;
    for(int i = 0; i < len; ++i)
        list.appendEl(i);

    IntBidiListIterator it1 = list.begin();
    IntBidiListIterator it2 = list.begin();
    EXPECT_EQ(true, it1 == it2);
    EXPECT_EQ(false, it1 != it2);

    it1++;
    EXPECT_EQ(false, it1 == it2);
    EXPECT_EQ(true, it1 != it2);

    it1--;
    EXPECT_EQ(true, it1 == it2);
    EXPECT_EQ(false, it1 != it2);
}
