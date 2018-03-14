#ifndef BROKENDNA_DNAELEMENT_H_
#define BROKENDNA_DNAELEMENT_H_

#include <iostream>
#include <string>

/** \brief Класс представляет собой простейшую структуру элемента ДНК.
 *
 *  Элемент ДНК включает следующие атрибуты: идентификатор (a..z), номер в цепочке, кислотное основание.
 */
class DNAElement {
public:

    /// Конструктор по умолчанию — нужен контейнерам
    DNAElement();

    /// Конструктор инициализации строкой
    DNAElement(const std::string& description);

public:

    /// enum, который содержит кислотные основания
    enum Base {
        Adenine = 'A', Cytosine = 'C', Thymine = 'T', Guanine = 'G'
    };


    /**
     * \brief Инициализирует объект на основе переданной строки.
     *
     * Fill the fields id, number, base from a description in the format [name][number]:[type] where
     * [id] - a..z
     * [number] - the number of this element in the DNA sequence a1 a2 a3 a4 a5...
     * [base] - biological component of the element (A, C, T or G)
     *
     * So for description "a1:G"
     * name = "a";
     * number = 1;
     * type = "G";
     *
     * Throws invalid_argument if the format is wrong
     *                      or if the type of element is not in [A, C, T, G]
     */
    void readFromString(const std::string& description);


    /// Определяет, является ли строка DNA элементом, записанным в строковом виде
    bool isCorrectDNAElement(std::string el);

    /// Выводит строковое представление объекта DNAElement в ostream
    friend std::ostream& operator<<(std::ostream& out, const DNAElement& subj);


public:

    /// Идентификатор элемента (a..z).
    std::string id;


    /// Номер элемента в ДНК.
    int number;

    /// Кислотное основание.
    Base base;

}; // class DNAElement

#endif // BROKENDNA_DNAELEMENT_H_
