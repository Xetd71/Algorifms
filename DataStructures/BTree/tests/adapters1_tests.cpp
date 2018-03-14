////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit-тесты для адаптеров для B-деревьев
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
////////////////////////////////////////////////////////////////////////////////





//#include <gtest/gtest.h>
#include <gtest/gtest.h>

#include "individual.h"
#include "../src/btree_adapters.h"


using namespace xi;


/** \brief Тестовый класс для тестирования открытых интерфейсов адаптеров для B-tree. */
class AdaptersTest : public ::testing::Test {
public:
    //BTreeTest()
    //    : _dumper(DUMP_EVENTLOG_PUB_FN, DUMP_IMGS_PUB_PATH)
    //{
    //}

public:
    //static const int STRUCT2_SEQ[];
    //static const int STRUCT2_SEQ_NUM;

    std::string& getFn(const char* fn)
    {
        _fn = TEST_FILES_PATH;
        _fn.append(fn);
        return _fn;
    }

protected:
    std::string _fn;        ///< Имя файла


protected:
    //RBTreeDefDumper<int, std::less<int>> _dumper;

    ///** \brief Выводить в формате GraphViz. */
    //RBTreeGvDumper<int, std::less<int>> _gvDumper;
}; // class RBTreePubTest






TEST_F(AdaptersTest, Simplest)
{
    //EXPECT_TRUE(tree.isEmpty());
}


TEST_F(AdaptersTest, IntAdapterCreate1)
{
    std::string fn(TEST_FILES_PATH);
    fn.append("IntAdapterCreate1.xibt");

    BTreeIntAdapter bt;
    bt.create(2, fn);


    // возьмем для дуобства ссылку на дерево
    FileBaseBTree& tr = bt.getTree();               // вопрос для подумать: что будет, если убрать & закорючку

    // основные свойства
    EXPECT_EQ(sizeof(int), tr.getRecSize());
    EXPECT_EQ(2, tr.getOrder());                    // 
    EXPECT_EQ(1, tr.getLastPageNum());
    EXPECT_EQ(1, tr.getRootPageNum());
}


TEST_F(AdaptersTest, IntAdSetGetKey1)
{
    std::string fn(TEST_FILES_PATH);
    fn.append("IntAdSetGetKey1.xibt");

    BTreeIntAdapter bt;
    bt.create(2, fn);


    // возьмем для дуобства ссылку на дерево
    FileBaseBTree& tr = bt.getTree();               // вопрос для подумать: что будет, если убрать & закорючку
    FileBaseBTree::PageWrapper wp(&tr);

    // создаем две страницы
    tr.allocPage(wp, 2, true);  //true);                          // на два ключа лист
    tr.allocPage(wp, 3, false);  //false);                         // на три ключа внутренний
    EXPECT_EQ(3, tr.getLastPageNum());

    // попишем в первую после корня страницу

    //tr.readWorkPage(1);
    wp.readPage(2);
    bt.setKey(wp, 0, 0x55AA55aa);                   // 0-й ключ
    bt.setKey(wp, 1, 0x66BB66BB);                   // 1-й (он же последний)
    //tr.writeWorkPage(1);
    wp.writePage();

    // попишем во вторую после корня страницу
    // tr.readWorkPage(2);
    wp.readPage(3);
    bt.setKey(wp, 0, 0x11);                         // 0-й ключ
    bt.setKey(wp, 1, 0x22);
    bt.setKey(wp, 2, 0x33);                         // 2-й (он же последний)
    //tr.writeWorkPage(2);
    wp.writePage();


    // теперь почитаем обратно
    //tr.readWorkPage(1);
    wp.readPage(2);
    EXPECT_EQ(0x55AA55aa, bt.getKey(wp, 0));
    EXPECT_EQ(0x66BB66BB, bt.getKey(wp, 1));


    //tr.readWorkPage(2);
    wp.readPage(3);
    EXPECT_EQ(0x11, bt.getKey(wp, 0));
    EXPECT_EQ(0x22, bt.getKey(wp, 1));
    EXPECT_EQ(0x33, bt.getKey(wp, 2));
}

TEST_F(AdaptersTest, Reopen1)
{
    std::string& fn = getFn("Reopen1.xibt");

    BTreeIntAdapter bt;
    bt.create(2, fn);


    // возьмем для дуобства ссылку на дерево
    FileBaseBTree& tr = bt.getTree();                   // вопрос для подумать: что будет, если убрать & закорючку
    FileBaseBTree::PageWrapper wp(&tr);

    // создаем две страницы
    tr.allocPage(wp, 2, true);                          // на два ключа лист
    tr.allocPage(wp, 3, false);                         // на три ключа внутренний
    EXPECT_EQ(3, tr.getLastPageNum());

    bt.close();


    // переоткрываем
    bt.open(fn);

    EXPECT_EQ(3, tr.getLastPageNum());
    EXPECT_EQ(1, tr.getRootPageNum());


}





