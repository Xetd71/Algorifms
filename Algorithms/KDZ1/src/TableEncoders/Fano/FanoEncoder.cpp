//
// Created by Ivan on 3/22/2018.
//

#include <algorithm>
#include <cmath>
#include "FanoEncoder.h"

void FanoEncoder::fillCodes(FanoNode* left, FanoNode* right, std::size_t total)
{
    //Находим медиану
    FanoNode* m = left;
    std::size_t leftSum = left->value;
    FanoNode* next = left + 1;
    while(abs((long)(leftSum + next->value - (total - leftSum - next->value))) < abs((long)(leftSum - (total - leftSum))))
    {
        leftSum += next->value;
        m = next;
        ++next;
    }

    FanoNode* i = left;
    //Задаем коды для левой части
    for(; i <= m; ++i)
        encodeTable[i->latter] += '0';
    //Задаем коды для правой части
    for(; i <= right; ++i)
        encodeTable[i->latter] += '1';

    //Рекурсивно задаем коды
    if(m - left > 0)
        fillCodes(left, m, leftSum);
    if(right - m > 1)
        fillCodes(m + 1, right, total - leftSum);
}

void FanoEncoder::createEncodeTable()
{
    std::size_t n = count.size(), i = 0, total = 0;
    FanoNode* nodes = new FanoNode[n];
    FanoNode fn;
    for(auto& node : count) {
        fn.latter = node.first;
        fn.value = node.second;
        nodes[i++] = fn;
        total += node.second;
    }
    std::sort(nodes, nodes + n - 1, FanoNode::less());

    fillCodes(nodes, nodes + n - 1, total);
    delete[] nodes;
}
