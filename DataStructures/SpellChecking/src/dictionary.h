/*
 * \file
 * \brief реализация классов hash_function, equality, Dictionary
 * \author Чуев Иван БПИ163
 * \date 19.11.2017
 *              Реализован класс hash_function
 *              Реализован класс Dictionary
 */


#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>

#include  "hashset.h"
#include  "hashset.cpp"

//using namespace std;

class hash_function {
public:
    hash_function()
    {
        unsigned int byte, crc, j;
        //Создаем таблицу для более быстрого хеширования
        for(byte = 0; byte < 256; byte++) {
            crc = byte;
            for(j = 8; j > 0; j--)
                crc = crc & 1 ? (crc >> 1) ^ CRC_POLYNOM : crc >> 1;
            table[byte] = crc;
        }
    }

    unsigned int operator()(const std::string& s) const
    {
        unsigned int byte, crc = 0xFFFFFFFF;
        //Хешируем строку посимвольно
        for(int i = 0; (byte = static_cast<unsigned char>(s[i])) != 0; i++)
            crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];
        return ~crc;
    }

public:

    //Полином CRC-32Q хеширования
    static const unsigned int CRC_POLYNOM = 0x814141AB;

protected:

    //Таблица для более быстрого хеширования
    unsigned int table[256];
};

class equality {
public:
    equality() {}

    bool operator()(const std::string& a, const std::string& b) const
    {
        return (a == b);
    }
};


class Dictionary : public HashSet<std::string, hash_function, equality> {
public:

    Dictionary(const std::string& filename)
    {
        //Пытаемся открыть файл. Если это не возможно, выбрасываем исключение
        std::ifstream inputFile;
        inputFile.open(filename, std::ifstream::in);
        if(!inputFile.is_open())
            throw std::runtime_error("Could not open file");

        //Построчно считываем слова из файла и записываем их в словарь
        std::string line;
        while(inputFile.good()) {
            std::getline(inputFile, line);
            insert(line);
        }
    }
};

#endif
