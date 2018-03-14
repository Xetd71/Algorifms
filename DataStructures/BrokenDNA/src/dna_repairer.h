#ifndef BROKENDNA_DNAREPAIRER_H_
#define BROKENDNA_DNAREPAIRER_H_

#include "dna_element.h"
#include "linked_list.h"

#include <map>


/** \brief Робот-починитель сломанных ДНК
 *
 *  Умеет читать текстовый файл с отдельным фрагментами сломанных ДНК и склеивать их
 *  в правильном порядке, без мутаций!
 */
class DNARepairer {
public:
    // Открытые типы

    /// Класс представляет связанных список ДНК-узлов, которые содержат \c DNAElement объекты.
    /// Узел не то же самое, что значение, которое он несет!
    typedef xi::LinkedList<DNAElement> DNAChain;

    /// Класс представляет один узел, который содержат \c DNAElement.
    /// Список ДНК состоит из узлов \c NodeDNA.
    typedef xi::Node<DNAElement> NodeDNA;

    /// Класс представляет список цепочек ДНК.
    typedef xi::LinkedList<DNAChain> ListOfDNAChains;

    /// Класс представляет один узел-цепочку ДНК.
    typedef xi::Node<DNAChain> NodeDNAChain;

    /// Отображение идентификатора цепочки ДНК на список, представляющий эту цепочку
    typedef std::map<std::string, DNAChain*> Id2DnaMap;


public:
    /// Возвращает ссылку на хранилище цепочек ДНК
    ListOfDNAChains& getDNAStorage();


    /// Загружает отдельные «куски» цепочек ДНК из текстового файла, имя которого 
    /// приходит в качестве параметра.
    /// Если файл не может быть открыт, генерирует исключительную ситуацию \c std::runtime_error.
    void readFile(const std::string& filename);

    /// Осуществляет восстановление всех загруженных цепочек ДНК.
    void repairDNA();

    /// Выводит содержимое хранилища цепочек ДНК в стандартный поток вывода.
    void printDNAStorage();

// Хелперные методы упрощающие работу repairDNA()
private:

    /** Если переданный элемент является началом "правильной" поледовательности, то возвращается конец этой последовательности
    *
    * "правильная" последовательность пример: a1:T a2:G a3:A
    * Если был передан элемент a1:T, а он является началом последовательности: a1:T a2:G a3:A b2:T
    * то данный метод вернет элемент a3:A
    *
    * \param[in] currentDNANode - элемент, возможно являющийся началом "правильной" поледовательности
    */
    NodeDNA* findWholeChunk(NodeDNA* currentDNANode);

    /** находит и возвращает элемент в \c currentDNAChain, после которого надо поставить элемент с цифрой \c number
    *
    * то есть если переданная цепочка имеет вид: a1:T a2:G a4:A
    * и подается элемент number = 3 (например для элемента a3:T)
    * то возвращается элемент a2:G
    *
    * \param[in] currentDNAChain - в которой ищется место для вставки
    * \param[in] number - номер элемента
    */
    NodeDNA* getDNANodeWithNumberLessThen(DNAChain* currentDNAChain, int number);

    /** Если в mapOfChains была найдена подходящая цепочка ддля элементов, то они переносятся в конец этой цепочки,
    * если цепочка не была найдена, то она создается и в нее переносятся переданные элементы
    *
    * Элементы переносятся с beforeDNANode->next по currentDNANode
    *
    * \param[in] mapOfChains - мапа с ссылками на цепочки DNAChain, ключами к которым являются id элементов
    * \param[in] beforeDNANode - элемент, после которого начинается перенос
    * \param[in] currentDNANode - последний переносимый элемент
    */
    void addToMapNewDNAElement(NodeDNA* beforeDNANode, NodeDNA* currentDNANode);

    /** Переносит цепочки из мапы mapOfChains в dnaStorage и удаляет оставшиеся хвосты в mapOfChains
    * \param[in] mapOfChains - мапа, в который хранятся цепочки
    * \param[in] dnaStorage - хранилище цепочек ДНК
    */
    void addNodesToDNAStorageFormMapOfNodeChains();


private:

    /// Хранилище цепочек ДНК.
    ListOfDNAChains _dnaStorage;

    /// мапа, которая хранит ссылки на DNAChain во время работы repairDNA()
    Id2DnaMap _mapOfChains;

}; // class DNARepairer



#endif // BROKENDNA_DNAREPAIRER_H_

