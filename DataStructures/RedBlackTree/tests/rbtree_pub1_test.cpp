#include <gtest/gtest.h>

#include "../src/rbtree.h"
#include "def_dumper.h"
#include "individual.h"


using namespace xi;

// Тестируем на целых числах.
typedef RBTree<int> RBTreeInt;


/** \brief Тестовый класс для тестирования открытых интерфейсов классов КЧД в виде черного ящика. */
class RBTreePubTest : public ::testing::Test {
public:
    RBTreePubTest() : _dumper(DUMP_EVENTLOG_PUB_FN, DUMP_IMGS_PUB_PATH)
    {
    }

public:
    static const int STRUCT2_SEQ[];
    static const int STRUCT2_SEQ_NUM;


protected:
    RBTreeDefDumper<int, std::less<int>> _dumper;

    /** \brief Выводить в формате GraphViz. */
    RBTreeGvDumper<int, std::less<int>> _gvDumper;
}; // class RBTreePubTest


// Вынесенная инициализация массива
const int RBTreePubTest::STRUCT2_SEQ[] = {4, 50, 10, 40, 17, 35, 20, 27, 37, 45, 60, 21, 1, 30};
const int RBTreePubTest::STRUCT2_SEQ_NUM = sizeof(STRUCT2_SEQ) / sizeof(STRUCT2_SEQ[0]);


TEST_F(RBTreePubTest, Simplest)
{
    //RBTree<int> tree;
    RBTreeInt tree;
    EXPECT_TRUE(tree.isEmpty());
}


// внешняя вставка элемента — добавление нода
TEST_F(RBTreePubTest, insert1)
{
    RBTreeInt tree;
    tree.setDumper(&_dumper);

    for(int i = 0; i < STRUCT2_SEQ_NUM; ++i) {
        tree.insert(STRUCT2_SEQ[i]);

        char fnBuf[255];
        sprintf(fnBuf, "%s\\Insert1_step_%03d.gv", DUMP_IMGS_PUB_PATH, i);
        _gvDumper.dump(fnBuf, tree);
    }


    //std::string fn1(DUMP_IMGS_PUB_PATH);
    //fn1.append("Insert1.gv");
    //_gvDumper.dump(fn1, tree);
}


// поиск элемента
TEST_F(RBTreePubTest, find1)
{
    RBTreeInt tree;

    for(int i = 0; i < STRUCT2_SEQ_NUM; ++i)
        tree.insert(STRUCT2_SEQ[i]);

    const RBTreeInt::Node* n4 = tree.find(4);           // черный
    EXPECT_EQ(4, n4->getKey());

    const RBTreeInt::Node* n20 = tree.find(20);         // корень
    EXPECT_EQ(20, n20->getKey());

    const RBTreeInt::Node* n35 = tree.find(35);         // красный
    EXPECT_EQ(35, n35->getKey());

    const RBTreeInt::Node* n30 = tree.find(30);         // лист
    EXPECT_EQ(30, n30->getKey());

    const RBTreeInt::Node* n100 = tree.find(100);       // отсутствующий элемент
    EXPECT_EQ(nullptr, n100);
}

// поиск элемента
TEST_F(RBTreePubTest, find2)
{
    // пустое дерево
    RBTreeInt tree;

    const RBTreeInt::Node* n4 = tree.find(4);
    EXPECT_EQ(nullptr, n4);

    const RBTreeInt::Node* n100 = tree.find(100);
    EXPECT_EQ(nullptr, n100);
}


#ifdef RBTREE_WITH_DELETION

// удаление нод
TEST_F(RBTreePubTest, delete1)
{
    RBTreeInt tree;

    for(int i = 0; i < STRUCT2_SEQ_NUM; ++i)
        tree.insert(STRUCT2_SEQ[i]);


    std::string fn1(DUMP_IMGS_PUB_PATH);
    fn1.append("delete1.gv");
    _gvDumper.dump(fn1, tree);

    // далее с пошаговой отладкой
    tree.setDumper(&_dumper);

    // удаляем в той же последовательности (а можно и в обратной попробовать)
    for(int i = 0; i < STRUCT2_SEQ_NUM; ++i)
        tree.remove(STRUCT2_SEQ[i]);

}

#endif // RBTREE_WITH_DELETION