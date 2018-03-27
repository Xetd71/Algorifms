//
// Created by Ivan on 3/23/2018.
//

#ifndef PROJECT_LZ77_H
#define PROJECT_LZ77_H


#include "../FileEncoder.h"

class LZ77Encoder : virtual public FileEncoder
{
public:
    LZ77Encoder(unsigned short int historyBufferSize, unsigned short int previewBufferSize) :
            historyBufferSize(historyBufferSize), previewBufferSize(previewBufferSize)
    {}

    void encode(std::istream& encoded,  std::ostream& decoded) override;

    void decode(std::istream& decoded,  std::ostream& encoded) override;

    unsigned short int getHistoryBufferSize() const;

    unsigned short int getPreviewBufferSize() const;

private:
    unsigned short int historyBufferSize;
    unsigned short int previewBufferSize;
};


#endif //PROJECT_LZ77_H
