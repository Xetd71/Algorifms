//
// Created by Ivan on 3/23/2018.
//

#include "TableEncoder.h"
#include <algorithm>


void TableEncoder::readDecodeTable(std::istream& file)
{
    char c, v;
    std::size_t z;
    int n = file.get(v) && (static_cast<unsigned char>(v) == 0) ? 256 : static_cast<unsigned char>(v);
    for(int i = 0; i < n; ++i) {
        file.get(c);
        file.get(v);
        z = static_cast<unsigned char>(v);
        file.get(v);
        z = (z << 8) | static_cast<unsigned char>(v);
        file.get(v);
        z = (z << 8) | static_cast<unsigned char>(v);
        file.get(v);
        z = (z << 8) | static_cast<unsigned char>(v);
        count[c] = z;
    }
    createDecodeTable();
}

void TableEncoder::writeDecodeTable(std::ostream& file)
{
    file << static_cast<char>((unsigned char)encodeTable.size());
    for(auto& v : count) {
        file << v.first;
        file << static_cast<char>(v.second >> 24);
        file << static_cast<char>((v.second >> 16) % 256);
        file << static_cast<char>((v.second >> 8) % 256);
        file << static_cast<char>(v.second % 256);
    }
}

void TableEncoder::encode(std::istream& encoded, std::ostream& decoded)
{
    countLetters(encoded);
    encoded.clear();
    encoded.seekg(0, encoded.beg);
    createEncodeTable();
    writeDecodeTable(decoded);

    char c;
    unsigned char out;
    std::string s = "";
    while(encoded.get(c)) {
        s += encodeTable[c];
        while(s.length() >= 8)
        {
            out = s[0] == '0' ? 0 : 1;
            for(int i = 1; i < 8; ++i)
                out = (out << 1) | (s[i] == '0' ? 0 : 1);
            s = s.substr(8);
            decoded << static_cast<char>(out);
        }
    }
    unsigned char lastOccupied = (unsigned char)(s.length() % 8);
    while(s.length() > 0) {
        std::size_t k = std::min(s.length(), (std::size_t)8);
        out = s[0] == '0' ? 0 : 1;
        for(int i = 1; i < k; ++i)
            out = (out << 1) | (s[i] == '0' ? 0 : 1);
        decoded << static_cast<char>(out);
        s = s.substr(k);
    }
    decoded << lastOccupied;
}

void TableEncoder::decode(std::istream& decoded, std::ostream& encoded)
{
    readDecodeTable(decoded);

    std::string s = "";
    char v3, v2, v1;
    decoded.get(v2);
    decoded.get(v1);
    while(true)
    {
        v3 = v2; v2 = v1;
        if(!decoded.get(v1))
            break;
        for(int k = 7; k >= 0; --k) {
            s += ((static_cast<unsigned char>(v3) >> k) & 1) == 0 ? '0' : '1';
            if(decodeTable.count(s) > 0) {
                encoded << decodeTable[s];
                s = "";
            }
        }
    }

    for(int k = static_cast<unsigned char>(v2) - 1; k >= 0; --k) {
        s += ((static_cast<unsigned char>(v3) >> k) & 1) == 0 ? '0' : '1';
        if(decodeTable.count(s) > 0) {
            encoded << decodeTable[s];
            s = "";
        }
    }
}

void TableEncoder::countLetters(std::istream& file)
{
    char c;
    while(file.get(c))
    {
        if(count.count(c) > 0)
            count[c] += 1;
        else
            count[c] = 1;
    }
}

void TableEncoder::createDecodeTable()
{
    createEncodeTable();
    for(auto& c : encodeTable)
        decodeTable[c.second] = c.first;
}

