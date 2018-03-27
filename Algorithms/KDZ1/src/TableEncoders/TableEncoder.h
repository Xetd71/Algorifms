//
// Created by Ivan on 3/23/2018.
//

#ifndef PROJECT_TABLEENCODER_H
#define PROJECT_TABLEENCODER_H

#include <fstream>
#include <map>
#include "../FileEncoder.h"

class TableEncoder : public virtual FileEncoder
{
public:

    virtual void createEncodeTable() = 0;

    void encode(std::istream& encoded,  std::ostream& decoded) override;

    void decode(std::istream& decoded,  std::ostream& encoded) override;

protected:

    void createDecodeTable();

    void readDecodeTable(std::istream& file);

    void writeDecodeTable(std::ostream& file);

    void countLetters(std::istream& file);

    std::map<char, std::size_t> count;

    std::map<char, std::string> encodeTable;

    std::map<std::string, char> decodeTable;

};

#endif //PROJECT_TABLEENCODER_H
