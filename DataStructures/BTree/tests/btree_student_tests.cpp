#include <gtest/gtest.h>


#include "individual.h"
#include "../src/btree.h"

using namespace xi;

class ByteComparator : public BaseBTree::IComparator {
public:
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


class BTreeStudentTest : public testing::Test {
public:
    std::string& getFn(const char* fn)
    {
        _fn = TEST_FILES_PATH;
        _fn.append(fn);
        return _fn;
    }

public:
    ByteComparator _cmp;

protected:
    std::string _fn;

};


TEST_F(BTreeStudentTest, insertNonFull_withoutComparator)
{
    FileBaseBTree tree(2, 1, nullptr, getFn("student_insertNonFull_withoutComparator.xibt"));

    FileBaseBTree::PageWrapper& pw = tree.getRootPage();

    Byte k1 = 0x03;
    EXPECT_THROW(pw.insertNonFull(&k1), std::runtime_error);
}

TEST_F(BTreeStudentTest, insertNonFull_leaf)
{
    FileBaseBTree tree(2, 1, &_cmp, getFn("student_insertNonFull_leaf.xibt"));

    FileBaseBTree::PageWrapper& pw = tree.getRootPage();

    Byte k1 = 0x03;
    pw.insertNonFull(&k1);
    EXPECT_EQ(1, pw.getKeysNum());
    EXPECT_TRUE(pw.isLeaf());
    EXPECT_TRUE(_cmp.isEqual(&k1, pw.getKey(0), 1));


    Byte k2 = 0x04;
    pw.insertNonFull(&k2);
    EXPECT_EQ(2, pw.getKeysNum());
    EXPECT_TRUE(pw.isLeaf());
    EXPECT_TRUE(_cmp.isEqual(&k1, pw.getKey(0), 1));
    EXPECT_TRUE(_cmp.isEqual(&k2, pw.getKey(1), 1));


    Byte k3 = 0x02;
    pw.insertNonFull(&k3);
    EXPECT_EQ(3, pw.getKeysNum());
    EXPECT_TRUE(pw.isLeaf());
    EXPECT_TRUE(_cmp.isEqual(&k3, pw.getKey(0), 1));
    EXPECT_TRUE(_cmp.isEqual(&k1, pw.getKey(1), 1));
    EXPECT_TRUE(_cmp.isEqual(&k2, pw.getKey(2), 1));


    EXPECT_THROW(pw.insertNonFull(&k3), std::domain_error);
}

TEST_F(BTreeStudentTest, insert)
{
    FileBaseBTree tree(2, 1, &_cmp, getFn("student_insert.xibt"));

    FileBaseBTree::PageWrapper& pw = tree.getRootPage();
    Byte k = 0x04;
    tree.insert(&k);
    k = 0x03;
    tree.insert(&k);
    k = 0x05;
    tree.insert(&k);
    k = 0x02;
    tree.insert(&k);


    EXPECT_EQ(1, pw.getKeysNum());
    EXPECT_FALSE(pw.isLeaf());
    k = 0x04;
    EXPECT_TRUE(_cmp.isEqual(&k, pw.getKey(0), 1));


    FileBaseBTree::PageWrapper pw2(&tree);
    pw2.readPageFromChild(pw, 0);
    EXPECT_EQ(2, pw2.getKeysNum());
    EXPECT_TRUE(pw2.isLeaf());
    k = 0x02;
    EXPECT_TRUE(_cmp.isEqual(&k, pw2.getKey(0), 1));
    k = 0x03;
    EXPECT_TRUE(_cmp.isEqual(&k, pw2.getKey(1), 1));


    pw2.readPageFromChild(pw, 1);
    EXPECT_EQ(1, pw2.getKeysNum());
    EXPECT_TRUE(pw2.isLeaf());
    k = 0x05;
    EXPECT_TRUE(_cmp.isEqual(&k, pw2.getKey(0), 1));
}


TEST_F(BTreeStudentTest, search)
{
    FileBaseBTree tree(2, 1, &_cmp, getFn("student_searsh.xibt"));
    Byte k = 0x04;
    tree.insert(&k);
    k = 0x03;
    tree.insert(&k);
    k = 0x05;
    tree.insert(&k);
    k = 0x02;
    tree.insert(&k);


    k = 0x04;
    EXPECT_TRUE(_cmp.isEqual(&k, tree.search(&k), 1));

    k = 0x03;
    EXPECT_TRUE(_cmp.isEqual(&k, tree.search(&k), 1));

    k = 0x02;
    EXPECT_TRUE(_cmp.isEqual(&k, tree.search(&k), 1));

    k = 0x05;
    EXPECT_TRUE(_cmp.isEqual(&k, tree.search(&k), 1));
}

TEST_F(BTreeStudentTest, searchAll)
{
    FileBaseBTree tree(2, 1, &_cmp, getFn("student_searsh.xibt"));
    Byte k = 0x04;
    tree.insert(&k);
    k = 0x03;
    tree.insert(&k);
    k = 0x05;
    tree.insert(&k);
    k = 0x02;
    const int n = 5;
    Byte keys[n] = {0x02, 0x02, 0x02, 0x02, 0x02};
    for(int i = 0; i < n; i++)
        tree.insert(&k);

    std::list<Byte*> foundKeys;
    EXPECT_EQ(n, tree.searchAll(&k, foundKeys));
    for(Byte* i : foundKeys)
        EXPECT_TRUE(_cmp.isEqual(i, &k, 1));
}