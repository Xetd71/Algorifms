#include <gtest/gtest.h>


// !!! uncomment this if you'd like to get the highest mark !!!
// раскомментируй эту строчку, если хочется получить оценочку повыше
// #define IWANNAGET10POINTS 



#include "../src/bidi_linked_list.h"

/** \brief Type alias for a list of integers */
typedef BidiLinkedList<int> IntBidiList;
typedef IntBidiList::Node IntBidiListNode;


TEST(BidiListInt, simpleCreate)
{
    // simply tests is a creation of a list works well
    IntBidiList lst;
    EXPECT_EQ(nullptr, lst.getHeadNode());
    EXPECT_EQ(nullptr, lst.getLastNode());
}

TEST(BidiListInt, emptySize)
{
    IntBidiList lst;
    
    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);
}


TEST(BidiListInt, append1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);
    EXPECT_EQ(nullptr, lst.getHeadNode());
    EXPECT_EQ(nullptr, lst.getLastNode());

    // append first element
    IntBidiListNode* nd1 = lst.appendEl(10);
    sz = lst.getSize();
    EXPECT_EQ(1, sz);
    EXPECT_NE(nullptr, lst.getHeadNode());
    EXPECT_NE(nullptr, lst.getLastNode());
    EXPECT_EQ(lst.getHeadNode(), lst.getLastNode());

    // append second
    IntBidiListNode* nd2 = lst.appendEl(20);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_NE(lst.getHeadNode(), lst.getLastNode());

    // test sequence
    EXPECT_EQ(nd1->getNext(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd1);
}

TEST(BidiListInt, insert1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);
    EXPECT_EQ(nullptr, lst.getHeadNode());
    EXPECT_EQ(nullptr, lst.getLastNode());


    // append first element
    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);

    EXPECT_EQ(nd1->getNext(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd1);

    // insert middle element
    IntBidiListNode* nd3 = new IntBidiListNode(15);
    // nd1->insertAfter(nd3);                           // can't proclaim this methos due to encapsulation reqs
    lst.insertNodeAfter(nd1, nd3);
    EXPECT_EQ(nd1->getNext(), nd3);
    EXPECT_EQ(nd3->getNext(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd3);
    EXPECT_EQ(nd3->getPrev(), nd1);

    // insert with a List method
    IntBidiListNode* nd4 = new IntBidiListNode(18);
    lst.insertNodeAfter(nd3, nd4);

    EXPECT_EQ(nd3->getNext(), nd4);
    EXPECT_EQ(nd4->getNext(), nd2);
    EXPECT_EQ(nd4->getPrev(), nd3);
    EXPECT_EQ(nd2->getPrev(), nd4);
}


TEST(BidiListInt, insertAfter1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    
    IntBidiListNode* nd1 = lst.insertNodeAfter(nullptr, new IntBidiListNode(10));
    sz = lst.getSize();
    EXPECT_EQ(1, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());

    IntBidiListNode* nd2 = lst.insertNodeAfter(nullptr, new IntBidiListNode(20));
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd2, lst.getLastNode());
    EXPECT_EQ(nd1->getNext(), nd2);

    IntBidiListNode* nd3 = lst.insertNodeAfter(nullptr, new IntBidiListNode(30));
    sz = lst.getSize();
    EXPECT_EQ(3, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd3, lst.getLastNode());
    EXPECT_EQ(nd1->getNext(), nd2);
    EXPECT_EQ(nd2->getNext(), nd3);
    EXPECT_EQ(nd3->getPrev(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd1);
}




/** \brief Helper function clears memory for given chain of nodes */
void clearNodes(IntBidiListNode* beg, IntBidiListNode* end)
{
    while (beg)
    {
        IntBidiListNode* nxt = beg->getNext();
        delete beg;
        beg = nxt;
    }
}




TEST(BidiListInt, cutNode1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    sz = lst.getSize();
    EXPECT_EQ(3, sz);

    IntBidiListNode* cutNd = lst.cutNode(nd2);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_EQ(cutNd, nd2);

    EXPECT_EQ(nd1->getNext(), nd3);
    EXPECT_EQ(nd3->getPrev(), nd1);

    delete cutNd;
}




TEST(BidiListInt, insNodesAfter2)
{
    IntBidiList lst1;

    size_t sz = lst1.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst1.appendEl(10);
    IntBidiListNode* nd1 = lst1.appendEl(20);
    IntBidiListNode* nd2 = lst1.appendEl(21);
    IntBidiListNode* nd3 = lst1.appendEl(22);
    IntBidiListNode* ndEnd = lst1.appendEl(30);

    sz = lst1.getSize();
    EXPECT_EQ(5, sz);

    // try to add some chains into another list
    IntBidiList lst2;
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, nd1, nd3), std::invalid_argument);
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, ndBeg, nd3), std::invalid_argument);
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, nd1, ndEnd), std::invalid_argument);
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, nd2, nd2), std::invalid_argument);

    // NOTE: uncheckable wrong operation:
    //ASSERT_THROW(lst2.insertNodesAfter(nullptr, ndBeg, ndEnd), std::invalid_argument);
}


TEST(BidiListInt, findFirst1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(22);
    IntBidiListNode* nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    // search empty
    IntBidiListNode* fnd = lst.findFirst(nullptr, 10);
    EXPECT_EQ(nullptr, fnd);

    // search first
    fnd = lst.findFirst(10);
    EXPECT_EQ(nd1, fnd);

    // search second from the same node
    fnd = lst.findFirst(fnd, 10);
    EXPECT_EQ(nd1, fnd);

    // search second from the next node
    fnd = lst.findFirst(fnd->getNext(), 10);
    EXPECT_EQ(nd3, fnd);

    // search third from the next node
    fnd = lst.findFirst(fnd->getNext(), 10);
    EXPECT_EQ(nd5, fnd);

    // search non-existing fourth
    fnd = lst.findFirst(fnd->getNext(), 10);
    EXPECT_EQ(nullptr, fnd);
}

TEST(BidiListInt, findAll1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(22);
    IntBidiListNode* nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    // search empty
    int fndSize = 0;
    IntBidiListNode** fnd = lst.findAll(nullptr, 10, fndSize);
    EXPECT_EQ(nullptr, fnd);

    // search first
    fnd = lst.findAll(10, fndSize);
    EXPECT_NE(nullptr, fnd);
    EXPECT_EQ(3, fndSize);
    EXPECT_EQ(nd1, fnd[0]);
    EXPECT_EQ(nd3, fnd[1]);
    EXPECT_EQ(nd5, fnd[2]);

    delete[] fnd;
    
    // search from second element
    fnd = lst.findAll(nd2, 10, fndSize);
    EXPECT_NE(nullptr, fnd);
    EXPECT_EQ(2, fndSize);
    EXPECT_EQ(nd3, fnd[0]);
    EXPECT_EQ(nd5, fnd[1]);

    delete[] fnd;

}


TEST(BidiListInt, cutFirst1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(22);
    IntBidiListNode* nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    IntBidiListNode* cutNd = lst.cutFirst(10);
    sz = lst.getSize();
    EXPECT_EQ(4, sz);
    EXPECT_EQ(cutNd, nd1);
    delete cutNd;


    cutNd = lst.cutFirst(nd4, 10);
    sz = lst.getSize();
    EXPECT_EQ(3, sz);
    EXPECT_EQ(cutNd, nd5);
    delete cutNd;

}




TEST(BidiListInt, cutNodes1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    lst.appendEl(21);
    IntBidiListNode* nd2 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(nd1, nd2);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);

    // clear memory
    clearNodes(nd1, nd2);
}

TEST(BidiListInt, cutNodes2)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(ndBeg, nd3);
    sz = lst.getSize();
    EXPECT_EQ(1, sz);

    EXPECT_EQ(ndEnd, lst.getHeadNode());
    EXPECT_EQ(nullptr, ndEnd->getPrev());
    EXPECT_EQ(nullptr, ndEnd->getNext());

    // clear memory
    clearNodes(ndBeg, nd3);
}

TEST(BidiListInt, cutNodes3)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(nd1, ndEnd);
    sz = lst.getSize();
    EXPECT_EQ(1, sz);

    EXPECT_EQ(ndBeg, lst.getHeadNode());
    EXPECT_EQ(nullptr, ndBeg->getPrev());
    EXPECT_EQ(nullptr, ndBeg->getNext());

    // clear memory
    clearNodes(nd1, ndEnd);
}

TEST(BidiListInt, cutNodes4)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(ndBeg, ndEnd);
    sz = lst.getSize();
    EXPECT_EQ(0, sz);

    EXPECT_EQ(nullptr, lst.getHeadNode());

    // clear memory
    clearNodes(ndBeg, ndEnd);
}

// this part of code is active only if you'd like to get the highest mark
#ifdef IWANNAGET10POINTS

TEST(BidiListInt, insNodesBefore1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);

    lst.insertNodesBefore(nullptr, nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    EXPECT_EQ(ndBeg->getNext(), ndEnd);
    EXPECT_EQ(ndEnd->getPrev(), ndBeg);

    EXPECT_EQ(nd3->getNext(), ndBeg);
    EXPECT_EQ(ndBeg->getPrev(), nd3);

    EXPECT_EQ(ndEnd->getNext(), nullptr);
    EXPECT_EQ(ndEnd->getPrev(), ndBeg);


    // put it back
    lst.cutNodes(nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);

    lst.insertNodesBefore(ndEnd, nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    EXPECT_EQ(ndBeg->getNext(), nd1);
    EXPECT_EQ(nd1->getPrev(), ndBeg);

    EXPECT_EQ(ndEnd->getPrev(), nd3);
    EXPECT_EQ(nd3->getNext(), ndEnd);
}





TEST(BidiListInt, insertBefore1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);


    IntBidiListNode* nd1 = lst.insertNodeBefore(nullptr, new IntBidiListNode(30));
    sz = lst.getSize();
    EXPECT_EQ(1, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());

    IntBidiListNode* nd2 = lst.insertNodeBefore(nullptr, new IntBidiListNode(20));
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_EQ(nd2, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());
    EXPECT_EQ(nd2->getNext(), nd1);

    IntBidiListNode* nd3 = lst.insertNodeBefore(nullptr, new IntBidiListNode(10));
    sz = lst.getSize();
    EXPECT_EQ(3, sz);
    EXPECT_EQ(nd3, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());
    EXPECT_EQ(nd3->getNext(), nd2);
    EXPECT_EQ(nd2->getNext(), nd1);
    EXPECT_EQ(nd1->getPrev(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd3);
}




TEST(BidiListInt, cutAll1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(22);
    IntBidiListNode* nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    // search empty
    int fndSize = 0;
    IntBidiListNode** fnd = lst.cutAll(nullptr, 10, fndSize);
    EXPECT_EQ(nullptr, fnd);

    // search first
    fnd = lst.cutAll(10, fndSize);

    sz = lst.getSize();
    EXPECT_EQ(2, sz);       // only two more elements should be left


    EXPECT_NE(nullptr, fnd);
    EXPECT_EQ(3, fndSize);
    EXPECT_EQ(nd1, fnd[0]);
    EXPECT_EQ(nd3, fnd[1]);
    EXPECT_EQ(nd5, fnd[2]);

    delete[] fnd;


}

#endif // IWANNAGET10POINTS
