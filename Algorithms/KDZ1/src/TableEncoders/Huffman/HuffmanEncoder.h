//
// Created by Ivan on 3/15/2018.
//

#ifndef KDZ1_HUFFMANENCODER_H
#define KDZ1_HUFFMANENCODER_H


#include <map>
#include <queue>
#include <fstream>
#include <vector>
#include "../../FileEncoder.h"
#include "../TableEncoder.h"

class HuffmanEncoder : virtual public TableEncoder
{
public:

    HuffmanEncoder() = default;

    void createEncodeTable() override;
};


#endif //KDZ1_HUFFMANENCODER_H
