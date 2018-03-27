//
// Created by Ivan on 3/22/2018.
//

#ifndef PROJECT_FANOENCODER_H
#define PROJECT_FANOENCODER_H


#include "../../FileEncoder.h"
#include "../TableEncoder.h"

class FanoEncoder : public virtual TableEncoder
{
public:

    FanoEncoder() = default;

    void createEncodeTable() override;

private:

    struct FanoNode
    {
        FanoNode() = default;

        FanoNode(std::size_t value, char latter) : value(value), latter(latter) {}

        struct less
        {
            bool operator()(const FanoNode& first, const FanoNode& second) const
            {
                return first.value > second.value;
            }
        };

        std::size_t value;
        char latter;
    };


private:

    void fillCodes(FanoNode* left, FanoNode* right, std::size_t total);
};


#endif //PROJECT_FANOENCODER_H
