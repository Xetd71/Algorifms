#include <gtest/gtest.h>


#include "individual.h"
#include "../src/btree.h"

using namespace xi;

class BTreeStudentTest_NM : public testing::Test {

public:
    std::string& getFn(const char* fn)
    {
        _fn = TEST_FILES_PATH;
        _fn.append(fn);
        return _fn;
    }

protected:
    std::string _fn;

};

struct ByteComparator : public BaseBTree::IComparator {
    virtual bool compare(const Byte* lhv, const Byte* rhv, UInt sz) override
    {
        if(*lhv < *rhv)
            return true;
        return false;
    }

    virtual bool isEqual(const Byte* lhv, const Byte* rhv, UInt sz) override
    {
        for(UInt i = 0; i < sz; ++i)
            if(*lhv != *rhv)
                return false;

        return true;
    }

};

TEST_F(BTreeStudentTest_NM, Search1)
{
    std::string& fn = getFn("Search1.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);

    const int n = 8;

    Byte elements[n] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    Byte* key = nullptr;

    for(int i = 0; i < n; i += 1) {
        key = bt.search(&elements[i]);

        EXPECT_EQ(nullptr, key);
    }
}

TEST_F(BTreeStudentTest_NM, Search2)
{
    std::string& fn = getFn("Search2.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);

    const int n = 8;

    Byte elements[n] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    for(int i = 0; i < n; ++i) {
        Byte& el = elements[i];
        bt.insert(&el);
    }

    Byte* key = nullptr;

    for(int i = 0; i < n; i += 1) {
        key = bt.search(&elements[i]);

        EXPECT_TRUE(comparator.isEqual(key, &elements[i], 1));

        delete[] key;
    }
}

TEST_F(BTreeStudentTest_NM, SearchAll1)
{
    std::string& fn = getFn("SearchAll1.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);

    const int n = 8;

    Byte elements[n] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    std::list<Byte*> keys;

    int count;

    for(int i = 0; i < n; i += 1) {
        count = bt.searchAll(&elements[i], keys);

        EXPECT_EQ(0, count);
    }
}

TEST_F(BTreeStudentTest_NM, SearchAll2)
{
    std::string& fn = getFn("SearchAll2.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);

    const int n = 8;

    Byte elements[n] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    for(int i = 0; i < n; ++i) {
        Byte& el = elements[i];
        bt.insert(&el);
    }

    std::list<Byte*> keys;

    int count;

    for(int i = 0; i < n; i += 1) {
        keys.clear();

        count = bt.searchAll(&elements[i], keys);

        EXPECT_EQ(1, count);

        EXPECT_TRUE(comparator.isEqual(keys.front(), &elements[i], 1));
    }
}

TEST_F(BTreeStudentTest_NM, SearchAll3)
{
    std::string& fn = getFn("SearchAll3.xibt");

    ByteComparator comparator;
    FileBaseBTree bt(2, 1, &comparator, fn);

    const int n = 8;

    Byte elements[n] = {0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02};

    for(int i = 0; i < n; ++i) {
        Byte& el = elements[i];
        bt.insert(&el);
    }

    std::list<Byte*> keys;

    int count = bt.searchAll(&elements[0], keys);

    EXPECT_EQ(4, count);

    for(Byte* key : keys)
        EXPECT_TRUE(comparator.isEqual(key, &elements[0], 1));
}