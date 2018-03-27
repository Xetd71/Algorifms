//
// Created by Ivan on 3/22/2018.
//

#ifndef PROJECT_FILEENCODER_H
#define PROJECT_FILEENCODER_H

#include <string>
#include <fstream>

class FileEncoder
{
public:
    void encodeFile(std::string encodedPath,  std::string decodedPath)
    {
        std::ifstream encodedFile(encodedPath, std::ifstream::in | std::ifstream::binary);
        std::ofstream file(decodedPath, std::ofstream::out | std::ofstream::binary);
        if(!encodedFile.good())
            throw std::invalid_argument("Can't open: " + encodedPath);
        if(!file.good())
            throw std::invalid_argument("Can't open: " + decodedPath);
        encode(encodedFile, file);
        encodedFile.close();
        file.close();
    }

    void decodeFile(std::string decodedPath, std::string encodedPath)
    {
        std::ifstream decodedFile(decodedPath, std::ifstream::in | std::ifstream::binary);
        std::ofstream file(encodedPath, std::ofstream::out | std::ofstream::binary);
        if(!decodedFile.good())
            throw std::invalid_argument("Can't open: " + encodedPath);
        if(!file.good())
            throw std::invalid_argument("Can't open: " + decodedPath);
        decode(decodedFile, file);
        decodedFile.close();
        file.close();
    }

    virtual void encode(std::istream& encoded,  std::ostream& decoded) = 0;

    virtual void decode(std::istream& decoded,  std::ostream& encoded) = 0;
};

#endif //PROJECT_FILEENCODER_H
