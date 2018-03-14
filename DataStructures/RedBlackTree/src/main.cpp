#include <iostream>

#include "rbtree.h"


using namespace std;


void simplestTest()
{
    using namespace xi;

    // просто создаем объект дерева
    RBTree<int> tree1;

    tree1.insert(5);
    tree1.insert(7);
    tree1.insert(6);
}


int main()
{
    cout << "Hello, World!" << endl;

    simplestTest();

    return 0;
}