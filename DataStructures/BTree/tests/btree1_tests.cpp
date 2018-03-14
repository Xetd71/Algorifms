////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit-тесты для B-деревьев
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
///
////////////////////////////////////////////////////////////////////////////////




//#include <gtest/gtest.h>
#include <gtest/gtest.h>


#include "individual.h"
#include "../src/btree.h"


using namespace xi;


/** \brief Тестовый класс для тестирования открытых интерфейсов B-tree. */
class BTreeTest : public ::testing::Test {
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
    //RBTreeDefDumper<int, std::less<int>> _dumper;

    ///** \brief Выводить в формате GraphViz. */
    //RBTreeGvDumper<int, std::less<int>> _gvDumper;
}; // class RBTreePubTest






TEST_F(BTreeTest, Simplest)
{
    //EXPECT_TRUE(tree.isEmpty());
}


TEST_F(BTreeTest, Order1)
{
    std::string fn(TEST_FILES_PATH);    // имя файла
    fn.append("order1.xibt");


    FileBaseBTree bt(2, 10, nullptr, fn);        // без компаратора!

    EXPECT_EQ(10, bt.getRecSize());

    EXPECT_EQ(2, bt.getOrder());
    EXPECT_EQ(3, bt.getMaxKeys());
    EXPECT_EQ(1, bt.getMinKeys());
    EXPECT_EQ(30, bt.getKeysSize());
    EXPECT_EQ(32, bt.getCursorsOfs()); // 30 + 2
    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48

    EXPECT_EQ(1, bt.getLastPageNum());
    EXPECT_EQ(1, bt.getRootPageNum());


    //EXPECT_TRUE(tree.isEmpty());
}


TEST_F(BTreeTest, AllocPage1)
{
    std::string fn(TEST_FILES_PATH);
    fn.append("AllocPage1.xibt");


    FileBaseBTree bt(2, 10, nullptr, fn);       // без компаратора!
    FileBaseBTree::PageWrapper wp(&bt);


    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48
    EXPECT_EQ(1, bt.getLastPageNum());

    // добавим пару страничек
    bt.allocPage(wp, 1, true);  //true);
    EXPECT_EQ(2, bt.getLastPageNum());

    bt.allocPage(wp, 2, false);  //false);
    EXPECT_EQ(3, bt.getLastPageNum());

    bt.allocPage(wp, 3, true);  //true);
    EXPECT_EQ(4, bt.getLastPageNum());


}


TEST_F(BTreeTest, ReadPage1)
{
    std::string fn(TEST_FILES_PATH);
    fn.append("ReadPage1.xibt");


    FileBaseBTree bt(2, 10, nullptr, fn);   // без компаратора!
    FileBaseBTree::PageWrapper wp(&bt);


    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48
    EXPECT_EQ(1, bt.getLastPageNum());

    // добавим пару страничек
    bt.allocPage(wp, 1, true);  //true);
    EXPECT_EQ(2, bt.getLastPageNum());

    bt.allocPage(wp, 2, false);  //false);
    EXPECT_EQ(3, bt.getLastPageNum());

    bt.allocPage(wp, 3, true);  //true);
    EXPECT_EQ(4, bt.getLastPageNum());

    // читаем странички (1-я теперь под корень!)
    //bt.readWorkPage(2);
    wp.readPage(2);
    EXPECT_TRUE(wp.isLeaf());
    EXPECT_EQ(1, wp.getKeysNum());

    //bt.readWorkPage(4);
    wp.readPage(4);
    EXPECT_TRUE(wp.isLeaf());
    EXPECT_EQ(3, wp.getKeysNum());

    //bt.readWorkPage(3);
    wp.readPage(3);
    EXPECT_FALSE(wp.isLeaf());
    EXPECT_EQ(2, wp.getKeysNum());
}


// тестируем запись модифицированных страничек
TEST_F(BTreeTest, WritePage1)
{
    std::string& fn = getFn("WritePage1.xibt");


    FileBaseBTree bt(2, 10, nullptr, fn);   // без компаратора!
    FileBaseBTree::PageWrapper wp(&bt);

    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48
    EXPECT_EQ(1, bt.getLastPageNum());

    // добавим пару страничек
    bt.allocPage(wp, 1, true);  //true);
    EXPECT_EQ(2, bt.getLastPageNum());

    bt.allocPage(wp, 2, false);  //false);
    EXPECT_EQ(3, bt.getLastPageNum());


    // читаем странички
    //bt.readWorkPage(2);
    wp.readPage(2);
    EXPECT_TRUE(wp.isLeaf());
    EXPECT_EQ(1, wp.getKeysNum());



    // модифицируем страничку 2
    wp.setLeaf(false);                // была истина
    *(wp.getKey(0)) = 'A';            // нумерация ключей — с нуля!!!
    //bt.writeWorkPage(2);
    wp.writePage();

    //bt.readWorkPage(3);
    wp.readPage(3);
    EXPECT_FALSE(wp.isLeaf());
    EXPECT_EQ(2, wp.getKeysNum());

    // модифицируем страничку 3
    wp.setKeyNum(3);                  // сделали три ключа на пробу!
    *(wp.getKey(1)) = 'B';
    //bt.writeWorkPage(3);
    wp.writePage();


    // еще раз читаем страницы
    //bt.readWorkPage(2);
    wp.readPage(2);
    EXPECT_FALSE(wp.isLeaf());        // теперь это должен быть не лист
    EXPECT_EQ(1, wp.getKeysNum());
    EXPECT_EQ('A', *(wp.getKey(0)));

    // еще раз читаем страницы
    //bt.readWorkPage(3);
    wp.readPage(3);
    EXPECT_FALSE(wp.isLeaf());
    EXPECT_EQ(3, wp.getKeysNum());    // теперь тут три ключа должно быть!
    EXPECT_EQ('B', *(wp.getKey(1)));

}


// тестируем запись модифицированных страничек через рабочие страницы
TEST_F(BTreeTest, WritePage2)
{
    std::string& fn = getFn("WritePage2.xibt");


    FileBaseBTree bt(2, 10, nullptr, fn);   // без компаратора!
    FileBaseBTree::PageWrapper wp(&bt);

    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48
    EXPECT_EQ(1, bt.getLastPageNum());

    // добавим пару страничек
    bt.allocPage(wp, 1, true);  //true);
    EXPECT_EQ(2, bt.getLastPageNum());

    bt.allocPage(wp, 2, false);  //false);
    EXPECT_EQ(3, bt.getLastPageNum());


    FileBaseBTree::PageWrapper wp1(&bt);

    // читаем и модифицируем страничку 2
    wp1.readPage(2);
    EXPECT_TRUE(wp1.isLeaf());
    EXPECT_EQ(1, wp1.getKeysNum());

    wp1.setLeaf(false);                // была истина
    *(wp1.getKey(0)) = 'A';            // нумерация ключей — с нуля!!!
    wp1.writePage();


    // читаем и модифицируем страничку 3
    wp1.readPage(3);
    EXPECT_FALSE(wp1.isLeaf());
    EXPECT_EQ(2, wp1.getKeysNum());

    wp1.setKeyNum(3);                   // сделали три ключа на пробу!
    *(wp1.getKey(1)) = 'B';             // нумерация ключей — с нуля!!!
    wp1.writePage();

    FileBaseBTree::PageWrapper wp2(&bt);

    // еще раз читаем страницы
    wp2.readPage(2);
    EXPECT_FALSE(wp2.isLeaf());
    EXPECT_EQ(1, wp2.getKeysNum());
    EXPECT_EQ('A', *(wp2.getKey(0)));

    wp2.readPage(3);
    EXPECT_FALSE(wp2.isLeaf());
    EXPECT_EQ(3, wp2.getKeysNum());
    EXPECT_EQ('B', *(wp2.getKey(1)));
}

// тестирует создание файла с последующим переотркрытием на том же объекте!
TEST_F(BTreeTest, ReopenFile1)
{
    std::string& fn = getFn("ReopenFile1.xibt");

    FileBaseBTree bt(2, 10, nullptr, fn);   // без компаратора!
    FileBaseBTree::PageWrapper wp(&bt);

    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48
    EXPECT_EQ(1, bt.getLastPageNum());

    // добавим пару страничек
    bt.allocPage(wp, 1, true);  //true);
    EXPECT_EQ(2, bt.getLastPageNum());

    bt.allocPage(wp, 2, false);  //false);
    EXPECT_EQ(3, bt.getLastPageNum());


    // читаем странички
    //bt.readWorkPage(2);
    wp.readPage(2);
    EXPECT_TRUE(wp.isLeaf());
    EXPECT_EQ(1, wp.getKeysNum());

    //bt.readWorkPage(3);
    wp.readPage(3);
    EXPECT_FALSE(wp.isLeaf());
    EXPECT_EQ(2, wp.getKeysNum());

    bt.close();


    // открываем заново
    bt.open(fn);    // , nullptr);
    EXPECT_EQ(10, bt.getRecSize());

    EXPECT_EQ(2, bt.getOrder());
    EXPECT_EQ(3, bt.getMaxKeys());
    EXPECT_EQ(1, bt.getMinKeys());
    EXPECT_EQ(30, bt.getKeysSize());
    EXPECT_EQ(32, bt.getCursorsOfs()); // 30 + 2
    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48

    EXPECT_EQ(3, bt.getLastPageNum());
    EXPECT_EQ(1, bt.getRootPageNum());

}

// тестирует создание файла с последующим переотркрытием в другом объекте!
TEST_F(BTreeTest, ReopenFile2)
{
    std::string& fn = getFn("ReopenFile2.xibt");

    FileBaseBTree bt(2, 10, nullptr, fn);   // без компаратора!
    FileBaseBTree::PageWrapper wp(&bt);

    EXPECT_EQ(48, bt.getNodePageSize()); // 32 + 4 * 4 = 48
    EXPECT_EQ(1, bt.getLastPageNum());

    // добавим пару страничек
    bt.allocPage(wp, 1, true);  //true);
    EXPECT_EQ(2, bt.getLastPageNum());

    bt.allocPage(wp, 2, false);  //false);
    EXPECT_EQ(3, bt.getLastPageNum());


    // читаем странички
    //bt.readWorkPage(2);
    wp.readPage(2);
    EXPECT_TRUE(wp.isLeaf());
    EXPECT_EQ(1, wp.getKeysNum());

    //bt.readWorkPage(3);
    wp.readPage(3);
    EXPECT_FALSE(wp.isLeaf());
    EXPECT_EQ(2, wp.getKeysNum());

    bt.close();


    // создаем новое дерево и открываем
    FileBaseBTree bt2(fn, nullptr);   // без компаратора!
    EXPECT_EQ(10, bt2.getRecSize());

    EXPECT_EQ(2, bt2.getOrder());
    EXPECT_EQ(3, bt2.getMaxKeys());
    EXPECT_EQ(1, bt2.getMinKeys());
    EXPECT_EQ(30, bt2.getKeysSize());
    EXPECT_EQ(32, bt2.getCursorsOfs()); // 30 + 2
    EXPECT_EQ(48, bt2.getNodePageSize()); // 32 + 4 * 4 = 48

    EXPECT_EQ(3, bt2.getLastPageNum());
    EXPECT_EQ(1, bt2.getRootPageNum());

}

TEST_F(BTreeTest, WorkPages1)
{
    std::string& fn = getFn("WorkPages1.xibt");

    FileBaseBTree bt(2, 10, nullptr, fn);   // без компаратора!
    FileBaseBTree::PageWrapper wp1(&bt);
    EXPECT_EQ(1, bt.getLastPageNum());

    // добавим пару страничек
    wp1.allocPage(1, true);
    EXPECT_EQ(2, bt.getLastPageNum());
    EXPECT_FALSE(wp1.isFull());


    wp1.allocPage(3, false);
    EXPECT_EQ(3, bt.getLastPageNum());
    EXPECT_TRUE(wp1.isFull());
}


TEST_F(BTreeTest, KeysNCursors1)
{
    std::string& fn = getFn("KeysNCursors1.xibt");

    FileBaseBTree bt(2, 10, nullptr, fn);
    FileBaseBTree::PageWrapper wp1(&bt);
    //FileBaseBTree::PageWrapper wp2(&bt);

    wp1.allocPage(1, false);
    *(wp1.getKey(0)) = 'A';
    EXPECT_EQ(nullptr, wp1.getKey(1));
    //ASSERT_THROW(*(wp1.getKey(1)) = 'B', DerivedClassException);

    wp1.setCursor(0, 1);
    wp1.setCursor(1, 2);
    ASSERT_THROW(wp1.setCursor(2, 42), std::invalid_argument);
    wp1.writePage();

    //EXPECT_E
}

TEST_F(BTreeTest, KeysNCursors2)
{
    std::string& fn = getFn("KeysNCursors2.xibt");


    FileBaseBTree bt(3, 2, nullptr, fn);
    FileBaseBTree::PageWrapper wp1(&bt);

    wp1.allocPage(3, false);
    *((UShort*) wp1.getKey(0)) = 0x0201;
    *((UShort*) wp1.getKey(1)) = 0x0207;
    *((UShort*) wp1.getKey(2)) = 0x0208;

    wp1.setCursor(0, 0xF0F0F0F0);           // отладочные бетолковые значения
    wp1.setCursor(1, 0xF1F1F1F1);
    wp1.setCursor(2, 0xF2F2F2F2);
    wp1.setCursor(3, 0xF3F3F3F3);

    wp1.writePage();

    FileBaseBTree::PageWrapper wp2(&bt);
    wp2.allocPage(5, false);  // nLeaf);
    *((UShort*) wp2.getKey(0)) = 0x0302;
    *((UShort*) wp2.getKey(1)) = 0x0303;
    *((UShort*) wp2.getKey(2)) = 0x0304;
    *((UShort*) wp2.getKey(3)) = 0x0305;
    *((UShort*) wp2.getKey(4)) = 0x0306;

    wp2.setCursor(0, 0xB0B0B0B0);           // отладочные бетолковые значения
    wp2.setCursor(1, 0xB1B1B1B1);
    wp2.setCursor(2, 0xB2B2B2B2);
    wp2.setCursor(3, 0xB3B3B3B3);
    wp2.setCursor(4, 0xB4B4B4B4);
    wp2.setCursor(5, 0xB5B5B5B5);


    wp2.writePage();

    // уст. курсор
    wp1.setCursor(1, wp2.getPageNum());         // ссылаемся на 3 страницу
    wp1.writePage();
}


TEST_F(BTreeTest, Split1)
{
    std::string& fn = getFn("Split1.xibt");


    FileBaseBTree bt(3, 2, nullptr, fn);
    FileBaseBTree::PageWrapper wp1(&bt);

    wp1.allocPage(3, false);
    *((UShort*) wp1.getKey(0)) = 0x0201;
    *((UShort*) wp1.getKey(1)) = 0x0207;
    *((UShort*) wp1.getKey(2)) = 0x0208;

    wp1.setCursor(0, 0xF0F0F0F0);           // отладочные бестолковые значения
    wp1.setCursor(1, 0xF1F1F1F1);
    wp1.setCursor(2, 0xF2F2F2F2);
    wp1.setCursor(3, 0xF3F3F3F3);

    wp1.writePage();

    FileBaseBTree::PageWrapper wp2(&bt);
    wp2.allocPage(5, false);  // nLeaf);
    *((UShort*) wp2.getKey(0)) = 0x0302;
    *((UShort*) wp2.getKey(1)) = 0x0303;
    *((UShort*) wp2.getKey(2)) = 0x0304;
    *((UShort*) wp2.getKey(3)) = 0x0305;
    *((UShort*) wp2.getKey(4)) = 0x0306;

    wp2.setCursor(0, 0xB0B0B0B0);           // отладочные бестолковые значения
    wp2.setCursor(1, 0xB1B1B1B1);
    wp2.setCursor(2, 0xB2B2B2B2);
    wp2.setCursor(3, 0xB3B3B3B3);
    wp2.setCursor(4, 0xB4B4B4B4);
    wp2.setCursor(5, 0xB5B5B5B5);


    wp2.writePage();

    // уст. курсор
    wp1.setCursor(1, wp2.getPageNum());         // ссылаемся на 3 страницу
    wp1.writePage();

    // выполняем собственно сплит
    wp1.splitChild(1);                          // курсор на 3 страницу

}

TEST_F(BTreeTest, Split2)
{
    std::string& fn = getFn("Split2.xibt");


    FileBaseBTree bt(2, 1, nullptr, fn);
    FileBaseBTree::PageWrapper wp1(&bt);

    wp1.allocPage(2, false);
    *(wp1.getKey(0)) = 0x01;
    *(wp1.getKey(1)) = 0x07;


    wp1.setCursor(0, 0xF0F0F0F0);           // отладочные бестолковые значения
    wp1.setCursor(1, 0xF1F1F1F1);
    wp1.setCursor(2, 0xF2F2F2F2);


    wp1.writePage();

    FileBaseBTree::PageWrapper wp2(&bt);
    wp2.allocPage(3, false);  // nLeaf);
    *(wp2.getKey(0)) = 0x08;
    *(wp2.getKey(1)) = 0x09;
    *(wp2.getKey(2)) = 0x0A;


    wp2.setCursor(0, 0xB0B0B0B0);           // отладочные бестолковые значения
    wp2.setCursor(1, 0xB1B1B1B1);
    wp2.setCursor(2, 0xB2B2B2B2);
    wp2.setCursor(3, 0xB3B3B3B3);


    wp2.writePage();

    // уст. курсор
    wp1.setCursor(2, wp2.getPageNum());     // ссылаемся на 3 страницу крайним правым курсором
    wp1.writePage();

    // выполняем собственно сплит
    wp1.splitChild(2);                      // 2-й курсор на 3 страницу

}


// простой сравниватель байт
struct ByteComparator : public BaseBTree::IComparator {
    virtual bool compare(const Byte* lhv, const Byte* rhv, UInt sz) override
    {
        if(*lhv < *rhv)
            return true;
        return false;
    }

    // простейшая реализация — побайтное сравнение
    virtual bool isEqual(const Byte* lhv, const Byte* rhv, UInt sz) override
    {
        for(UInt i = 0; i < sz; ++i)
            if(*lhv != *rhv)
                return false;

        return true;
    }


};


TEST_F(BTreeTest, InsertNonFull1)
{
    std::string& fn = getFn("InsertNonFull1.xibt");

    ByteComparator comparator;

    FileBaseBTree bt(2, 1, &comparator, fn);
    FileBaseBTree::PageWrapper wp1(&bt);

    wp1.allocPage(2, false);
    *(wp1.getKey(0)) = 0x05;
    *(wp1.getKey(1)) = 0x11;


    //wp1.setCursor(0, 0xF0F0F0F0);           // отладочные бестолковые значения
    //wp1.setCursor(1, 0xF1F1F1F1);
    //wp1.setCursor(2, 0xF2F2F2F2);


    wp1.writePage();

    FileBaseBTree::PageWrapper wp2(&bt);
    wp2.allocPage(2, true);  // nLeaf);
    *(wp2.getKey(0)) = 0x01;
    *(wp2.getKey(1)) = 0x03;
    wp2.writePage();

    FileBaseBTree::PageWrapper wp3(&bt);
    wp3.allocPage(2, true);  // nLeaf);
    *(wp3.getKey(0)) = 0x07;
    *(wp3.getKey(1)) = 0x09;
    wp3.writePage();

    FileBaseBTree::PageWrapper wp4(&bt);
    wp4.allocPage(2, true);  // nLeaf);
    *(wp4.getKey(0)) = 0x13;
    *(wp4.getKey(1)) = 0x15;
    wp4.writePage();



    //wp2.setCursor(0, 0xB0B0B0B0);           // отладочные бестолковые значения
    //wp2.setCursor(1, 0xB1B1B1B1);
    //wp2.setCursor(2, 0xB2B2B2B2);    
    //wp2.writePage();

    // уст. курсор
    wp1.setCursor(0, wp2.getPageNum());
    wp1.setCursor(1, wp3.getPageNum());
    wp1.setCursor(2, wp4.getPageNum());
    wp1.writePage();


    // вставляем 1 в "верхний" узел
    Byte k = 0x02;
    wp1.insertNonFull(&k);

    // теперь в заполненный добавим
    //k = 0x04;                         // это норм
    k = 0x02;
    wp1.insertNonFull(&k);
}


TEST_F(BTreeTest, Insert1)
{
    std::string& fn = getFn("Insert1.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);


    Byte k = 0x03;
    bt.insert(&k);

    k = 0x02;
    bt.insert(&k);

    k = 0x01;
    bt.insert(&k);
}

TEST_F(BTreeTest, Insert2)
{
    std::string& fn = getFn("Insert2.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);


    Byte k = 0x03;
    bt.insert(&k);

    k = 0x02;
    bt.insert(&k);

    k = 0x01;
    bt.insert(&k);

    k = 0x04;
    bt.insert(&k);
}


TEST_F(BTreeTest, Insert3)
{
    std::string& fn = getFn("Insert3.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);


    Byte els[] = {0x01, 0x11, 0x09, 0x05, 0x07, 0x03, 0x03};
    for(int i = 0; i < sizeof(els) / sizeof(els[0]); ++i) {
        Byte& el = els[i];
        bt.insert(&el);
    }


    //Byte k = 0x03;
    //bt.insert(&k);

    //k = 0x02;
    //bt.insert(&k);

    //k = 0x01;
    //bt.insert(&k);

    //k = 0x04;
    //bt.insert(&k);
}
