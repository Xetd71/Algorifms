#include "dna_element.h"
#include <iostream>
#include <string>

#pragma region Helpers

/// строка, помогающая определить корректность id
const std::string sDigits = "0123456789";

/// строка, помогающая определить корректность number
const std::string sSymbols = "abcdefghigklmnopqrstuvwxyz";

/// строка, помогающая определить корректность base
const std::string sBase = "ACTG";

bool isNumber(std::string str)
{
    if(sDigits.find(str[0], 1) == -1)           // первая цифра не может быть 0
        return false;

    for(size_t i = 1; i < str.length(); i++)
        if(sDigits.find(str[0]) == -1)
            return false;

    return true;
}

#pragma endregion


DNAElement::DNAElement()
{
    id = "";
    number = -1;
    base = Adenine;
}


DNAElement::DNAElement(const std::string& description)
{
    readFromString(description);                         //инициализирует поля создаваемого объекта
}


void DNAElement::readFromString(const std::string& description)
{
    if(!isCorrectDNAElement(description))
        throw std::invalid_argument("DNA element format is wrong");

    id = description[0];

    number = std::stoi(description.substr(1, description.length() - 3));            // переводит строку в число

    base = static_cast<Base>(description[3]);                                       // кастит символ кислотного основания к Base
}


bool DNAElement::isCorrectDNAElement(std::string el)
{
    // проверяем, что поданая строка имеет формат "[a..z][number]:[Base]"
    return sSymbols.find(el[0]) != -1 && isNumber(el.substr(1, el.length() - 3)) && el[2] == ':' &&
           sBase.find(el[3]) != -1;
}


std::ostream& operator<<(std::ostream& out, const DNAElement& subj)
{
    // выводит строковое представление элемента в out
    out << subj.id << subj.number << ":" << static_cast<char>(subj.base);
    return out;
}



// TODO: implement
