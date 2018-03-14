#include <gtest/gtest.h>

#include "../src/rbtree.h"
#include "def_dumper.h"
#include "individual.h"


namespace xi {

/** \brief Тестовый класс для тестирования закрытой части классов черно-красного дерева.
 *
 *  Данный класс, с одной стороны, представляется полноценный g-тестером, с другой —
 *  ему классы КЧД представляют дружественные полномочия, поэтому он может смело
 *  покопаться во внутренностях этих классов.
 */
    template<typename Element, typename Compar = std::less<Element> >
    class RBTreeTest : public ::testing::Test {
    public:
        // Объявление типов дерева и узла для упрощения доступа
        typedef RBTree<Element, Compar> TTree;
        typedef typename RBTree<Element, Compar>::Node TTreeNode;
        typedef typename RBTree<Element, Compar>::Color TTreeColor;

    public:
        static const int STRUCT2_SEQ[];
        static const int STRUCT2_SEQ_NUM;

    public:
        RBTreeTest()
        //: _dumper(DUMP_EVENTLOG_PRV_FN, DUMP_IMGS_PRV_PATH)
        {
        }

    protected:

        /** \brief Возвращает ссылку на неконстантный указатель на корень дерева \c tree.
         *
         *  Обратите внимание на это чудесное сочетание звездочек и амперсандиков!
         *  Оно не случайно...
         */
        typename IRBTreeDumper<Element, Compar>::TTreeNode*& getRootNode(TTree* tree)
        {
            return tree->_root;
        }


        /** \brief Создает узел без привязки к дереву */
        typename IRBTreeDumper<Element, Compar>::TTreeNode*
        createNode(const Element& key = Element(), typename IRBTreeDumper<Element, Compar>::TTreeNode* left = nullptr,
                   typename IRBTreeDumper<Element, Compar>::TTreeNode* right = nullptr,
                   typename IRBTreeDumper<Element, Compar>::TTreeNode* parent = nullptr,
                   typename RBTree<Element, Compar>::Color col = TTree::BLACK)
        {
            TTreeNode* newNode = new TTreeNode(key, left, right, parent, col);

            return newNode;
        }

        /** \brief Вращает узел \c node влево. */
        void rotNodeLeft(TTree* tree, TTreeNode* node)
        {
            tree->rotLeft(node);
        }


        /** \brief Вращает узел \c node вправо. */
        void rotNodeRight(TTree* tree, TTreeNode* node)
        {
            tree->rotRight(node);
        }

        /** \brief Для данного узла возвращает его левого потомка. */
        typename IRBTreeDumper<Element, Compar>::TTreeNode* getLeftChild(TTreeNode* node)
        {
            return node->_left;
        }

        /** \brief Для данного узла возвращает его правого потомка. */
        typename IRBTreeDumper<Element, Compar>::TTreeNode* getRightChild(TTreeNode* node)
        {
            return node->_right;
        }

        /** \brief Для данного узла возвращает его предка. */
        typename IRBTreeDumper<Element, Compar>::TTreeNode* getParentChild(TTreeNode* node)
        {
            return node->_parent;
        }

        /** \brief Вставляет элемент \c el в BST без учета свойств КЧД. */
        typename IRBTreeDumper<Element, Compar>::TTreeNode* insertNewBstEl(TTree* tree, const Element& el)
        {
            return tree->insertNewBstEl(el);
        }


    protected:
        // Некоторые методы инициализации деревьев
        TTree& createStruct1(TTree& tree)
        {
            // создаем структуру с [Рисунка 1]

            TTreeNode* n1 = createNode(1);
            TTreeNode* n4 = createNode(4);
            TTreeNode* n6 = createNode(6);
            TTreeNode* n5 = createNode(5, n4, n6);
            TTreeNode* n3 = createNode(3, n1, n5);

            // устанавливаем 3 как корень
            TTreeNode*& rt = getRootNode(&tree);
            rt = n3;

            return tree;
        }


    protected:
        //RBTreeDefDumper<Element, Compar> _dumper;

        /** \brief Выводить в формате GraphViz. */
        RBTreeGvDumper<Element, Compar> _gvDumper;

    }; // class RBTreeTest


// Вынесенная инициализация массива
    template<typename Element, typename Compar> const int RBTreeTest<Element, Compar>::STRUCT2_SEQ[] = {4, 50, 10, 40,
                                                                                                        17, 35, 20, 27,
                                                                                                        37, 45, 60, 21,
                                                                                                        1, 30};

    template<typename Element, typename Compar> const int RBTreeTest<Element, Compar>::STRUCT2_SEQ_NUM =
            sizeof(STRUCT2_SEQ) / sizeof(STRUCT2_SEQ[0]);


// Тестируем на целых числах.
    typedef RBTree<int> RBTreeInt;

// Конкретизация шаблонного класса для далеетестируемого целочисленного дерева
    typedef RBTreeTest<int> RBTreeIntTester;


    TEST_F(RBTreeIntTester, Simplest)
    {
        RBTreeInt tree;

        TTreeNode*& rt = getRootNode(&tree);
        EXPECT_EQ(nullptr, rt);
    }

// тестирует ручное добавление корня
    TEST_F(RBTreeIntTester, AddRootManually)
    {
        RBTreeInt tree;

        // берем ссылку на корень
        TTreeNode*& rt = getRootNode(&tree);
        rt = createNode();
        EXPECT_NE(nullptr, rt);
        EXPECT_FALSE(tree.isEmpty());           // теперь должен быть непустым!
    }


// создание простой структуры дерева
    TEST_F(RBTreeIntTester, SimpleStruct1)
    {
        // создаем структуру с [Рисунка 1]
        RBTreeInt tree;
        createStruct1(tree);

        // выводим в отладочный файл
        std::string fn(DUMP_IMGS_PRV_PATH);
        fn.append("SimpleStruct1.gv");

        _gvDumper.dump(fn, tree);

    }


// левый поворот
    TEST_F(RBTreeIntTester, LeftRot1)
    {
        // создаем структуру с [Рисунка 1]
        RBTreeInt tree;
        createStruct1(tree);

        // выводим в отладочный файл до
        std::string fn1(DUMP_IMGS_PRV_PATH);
        fn1.append("LeftRot1Before.gv");
        _gvDumper.dump(fn1, tree);

        // вращаем относительно n3 влево
        TTreeNode*& rt = getRootNode(&tree);
        TTreeNode* n3 = rt;                     // сохраняем для последующего изучения
        TTreeNode* n5 = getRightChild(n3);
        rotNodeLeft(&tree, rt);

        // выводим в отладочный файл после
        std::string fn2(DUMP_IMGS_PRV_PATH);
        fn2.append("LeftRot1After.gv");
        _gvDumper.dump(fn2, tree);


        // постусловия
        EXPECT_EQ(5, rt->getKey());
        EXPECT_EQ(nullptr, rt->getParent());


        EXPECT_EQ(nullptr, n5->getParent());
        EXPECT_EQ(n5, n3->getParent());
        EXPECT_EQ(n3, n5->getLeft());
    }


// правый поворот 1
    TEST_F(RBTreeIntTester, RightRot1)
    {
        // создаем структуру с [Рисунка 1]
        RBTreeInt tree;
        createStruct1(tree);

        // выводим в отладочный файл до
        std::string fn1(DUMP_IMGS_PRV_PATH);
        fn1.append("RightRot1Before.gv");
        _gvDumper.dump(fn1, tree);


        TTreeNode*& rt = getRootNode(&tree);
        TTreeNode* n5 = getRightChild(rt);

        TTreeNode* n4 = getLeftChild(n5);       // эти два для посл. изучения
        TTreeNode* n6 = getRightChild(n5);

        // вращаем относительно n5 вправо
        rotNodeRight(&tree, n5);

        // выводим в отладочный файл после
        std::string fn2(DUMP_IMGS_PRV_PATH);
        fn2.append("RightRot1After.gv");
        _gvDumper.dump(fn2, tree);


        // постусловия
        EXPECT_EQ(3, rt->getKey());
        EXPECT_EQ(nullptr, rt->getParent());

        EXPECT_EQ(n4, rt->getRight());
        EXPECT_EQ(rt, n4->getParent());

        EXPECT_EQ(n5, n4->getRight());
        EXPECT_EQ(nullptr, n4->getLeft());
        EXPECT_EQ(nullptr, n5->getLeft());

        EXPECT_EQ(n6, n5->getRight());
        EXPECT_EQ(n5, n6->getParent());

    }



// правый поворот 2
    TEST_F(RBTreeIntTester, RightRot2)
    {
        // создаем структуру с [Рисунка 1]
        RBTreeInt tree;
        createStruct1(tree);

        // выводим в отладочный файл до
        std::string fn1(DUMP_IMGS_PRV_PATH);
        fn1.append("RightRot2Before.gv");
        _gvDumper.dump(fn1, tree);



        // сохраняем указатели на инд. узлы
        TTreeNode*& rt = getRootNode(&tree);
        TTreeNode* n3 = rt;
        TTreeNode* n5 = getRightChild(rt);
        TTreeNode* n1 = getLeftChild(rt);
        TTreeNode* n4 = getLeftChild(n5);       // эти два для посл. изучения
        TTreeNode* n6 = getRightChild(n5);

        rotNodeRight(&tree, n3);


        // выводим в отладочный файл после
        std::string fn2(DUMP_IMGS_PRV_PATH);
        fn2.append("RightRot2After.gv");
        _gvDumper.dump(fn2, tree);


        // постусловия
        EXPECT_EQ(nullptr, n1->getParent());
        EXPECT_EQ(n1, n3->getParent());

        EXPECT_EQ(nullptr, n1->getLeft());
        EXPECT_EQ(nullptr, n3->getLeft());

        EXPECT_EQ(n5, n3->getRight());
        EXPECT_EQ(n3, n5->getParent());

    }


// левый поворот 2
    TEST_F(RBTreeIntTester, LeftRot2)
    {
        // создаем структуру с [Рисунка 1]
        RBTreeInt tree;
        createStruct1(tree);

        // выводим в отладочный файл до
        std::string fn1(DUMP_IMGS_PRV_PATH);
        fn1.append("LeftRot2Before.gv");
        _gvDumper.dump(fn1, tree);



        // сохраняем указатели на инд. узлы
        TTreeNode*& rt = getRootNode(&tree);
        TTreeNode* n3 = rt;
        TTreeNode* n5 = getRightChild(rt);
        TTreeNode* n1 = getLeftChild(rt);
        TTreeNode* n4 = getLeftChild(n5);       // эти два для посл. изучения
        TTreeNode* n6 = getRightChild(n5);

        rotNodeLeft(&tree, n5);


        // выводим в отладочный файл после
        std::string fn2(DUMP_IMGS_PRV_PATH);
        fn2.append("LeftRot2After.gv");
        _gvDumper.dump(fn2, tree);


        // постусловия
        EXPECT_EQ(nullptr, n3->getParent());
        EXPECT_EQ(n3, n1->getParent());
        EXPECT_EQ(n3, n6->getParent());
        EXPECT_EQ(n1, n3->getLeft());
        EXPECT_EQ(n6, n3->getRight());

        EXPECT_EQ(nullptr, n6->getRight());
        EXPECT_EQ(n5, n6->getLeft());

        EXPECT_EQ(n6, n5->getParent());
        EXPECT_EQ(nullptr, n5->getRight());
        EXPECT_EQ(n4, n5->getLeft());
    }



// внутренняя вставка элемента — добавление нода
    TEST_F(RBTreeIntTester, insertNewBstEl1)
    {
        RBTreeInt tree;

        for(int i = 0; i < STRUCT2_SEQ_NUM; ++i)
            insertNewBstEl(&tree, STRUCT2_SEQ[i]);


        std::string fn1(DUMP_IMGS_PRV_PATH);
        fn1.append("InsertNewBstEl1.gv");
        _gvDumper.dump(fn1, tree);
    }

    TEST_F(RBTreeIntTester, my_simple)
    {
        RBTreeInt tree;

        tree.insert(8);
        tree.insert(5);
        tree.insert(9);
        tree.insert(1);
        tree.insert(3);
        tree.insert(10);
        tree.insert(2);
        tree.insert(20);
        tree.insert(15);
        tree.insert(25);
        tree.insert(18);

        tree.remove(10);
        tree.remove(15);
        tree.remove(18);
        tree.remove(20);


        std::string fn1("../../");
        fn1.append("my.gv");
        _gvDumper.dump(fn1, tree);
    }


} // namespace xi