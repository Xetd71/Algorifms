//
// Created by Ivan on 3/15/2018.
//

#include "HuffmanEncoder.h"

struct HuffmanNode
{
    HuffmanNode(char latter, std::size_t value)
    {
        this->value = value;
        this->lattersToCodes[latter] = "";
    }

    HuffmanNode& concatenate(HuffmanNode& hNode)
    {
        for(auto& code : lattersToCodes)
            code.second = '1' + code.second;

        for(auto& code : hNode.lattersToCodes)
            code.second = '0' + code.second;

        this->value += hNode.value;
        this->lattersToCodes.insert(hNode.lattersToCodes.begin(), hNode.lattersToCodes.end());
        return *this;
    }

    struct less
    {
        bool operator()(const HuffmanNode& first, const HuffmanNode& second) const
        {
            return first.value > second.value;
        }
    };

    std::size_t value;
    std::map<char, std::string> lattersToCodes;
};

void HuffmanEncoder::createEncodeTable()
{
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, HuffmanNode::less> pq;

    for(auto& hNode : count)
        pq.push(HuffmanNode(hNode.first, hNode.second));

    while(pq.size() > 1)
    {
        HuffmanNode a = pq.top();
        pq.pop();
        HuffmanNode b = pq.top();
        pq.pop();
        pq.push(a.concatenate(b));
    }

    encodeTable = pq.top().lattersToCodes;
}
