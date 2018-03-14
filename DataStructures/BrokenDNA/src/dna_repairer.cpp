#include "dna_repairer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>


DNARepairer::NodeDNA* DNARepairer::findWholeChunk(NodeDNA* currentDNANode)
{
    NodeDNA* nextDNANode = currentDNANode->next;
    DNAElement currentElement = currentDNANode->value;
    DNAElement nextElement;

    while(nextDNANode != nullptr) {

        currentElement = currentDNANode->value;
        nextElement = nextDNANode->value;

        // Если чледующий элемент цепочки портит ее "правильность", то происходит выход из цикла и возвращается текущий элемент
        if(currentElement.id != nextElement.id || currentElement.number > nextElement.number)
            break;

        currentDNANode = nextDNANode;
        nextDNANode = currentDNANode->next;
    }

    return currentDNANode;
}


DNARepairer::NodeDNA* DNARepairer::getDNANodeWithNumberLessThen(DNAChain* currentDNAChain, int number)
{
    NodeDNA* currentDNANode = currentDNAChain->getPreHead();
    NodeDNA* nextDNANode = currentDNANode->next;

    // находит последний элемент, номер кторого меньше number
    while(nextDNANode != nullptr) {
        if(nextDNANode->value.number > number)
            break;
        currentDNANode = nextDNANode;
        nextDNANode = currentDNANode->next;
    }

    return currentDNANode;
}


void DNARepairer::addToMapNewDNAElement(NodeDNA* beforeDNANode, NodeDNA* currentDNANode)
{
    DNAElement currentElement = currentDNANode->value;
    DNAChain* currentDNAChain;
    Id2DnaMap::iterator mapOfChainsIterator = _mapOfChains.find(currentElement.id);

    if(mapOfChainsIterator == _mapOfChains.end()) {
        // Если в мапе не нашлось цепочки с данной id, то она добавляется в мап, и присваивается currentDNAChain
        try {
            currentDNAChain = new DNAChain();
        } catch(std::bad_alloc e) {
            std::cout << e.what();
            exit(EXIT_FAILURE);
        }

        _mapOfChains[currentElement.id] = currentDNAChain;
    } else
        // Если в мапе нашлась цепочка с данной id, то она присваивается currentDNAChain
        currentDNAChain = mapOfChainsIterator->second;

    // в currentDNAChain добавляются элементы с beforeDNANode->next по currentDNANode после нужного элемента
    currentDNAChain->moveNodesAfter(getDNANodeWithNumberLessThen(currentDNAChain, currentElement.number), beforeDNANode,
                                    currentDNANode);
}


void DNARepairer::addNodesToDNAStorageFormMapOfNodeChains()
{
    NodeDNAChain* nextNodeDNAChain = _dnaStorage.getPreHead()->next;
    NodeDNAChain* currentNodeDNAChain;
    for(char c = 'a'; c <= 'z'; c++) {
        Id2DnaMap::iterator mapOfChainsIterator = _mapOfChains.find(std::string(1, c));
        if(mapOfChainsIterator != _mapOfChains.end()) {
            if(nextNodeDNAChain == nullptr) {
                // если не хватает элементов в dnaStorage, то они создаются
                try {
                    nextNodeDNAChain = new NodeDNAChain();
                } catch(std::bad_alloc e) {
                    std::cout << e.what();
                    exit(EXIT_FAILURE);
                }
                currentNodeDNAChain->next = nextNodeDNAChain;
            }

            currentNodeDNAChain = nextNodeDNAChain;
            nextNodeDNAChain = currentNodeDNAChain->next;

            // чепочка из мапы добавляется в dnaStorage
            currentNodeDNAChain->value.getPreHead()->next = mapOfChainsIterator->second->getPreHead()->next;
            mapOfChainsIterator->second->getPreHead()->next = nullptr;

            // очищается оставшийся хвост в мапе
            delete mapOfChainsIterator->second;
            mapOfChainsIterator->second = nullptr;
        }
    }
}


void DNARepairer::repairDNA()
{
    // Chain из которой ведется считывание
    NodeDNAChain* currentDNAChain = _dnaStorage.getPreHead()->next;
    // проходим по строчкам (DNAChain)
    while(currentDNAChain != nullptr) {
        NodeDNA* beforeDNANode = currentDNAChain->value.getPreHead();
        NodeDNA* currentDNANode = beforeDNANode->next;

        // проходим по элементам в строчках (NodeDNA)
        while(currentDNANode != nullptr) {
            // находим подряд идущую цепочку (пр. a1:T a2:G a3:T) и перемещаем currentDNANode на последний ее элемент
            currentDNANode = findWholeChunk(currentDNANode);

            // перемещаем в _mapOfNodeChains элементы с beforeDNANode->next по currentDNANode включительно
            addToMapNewDNAElement(beforeDNANode, currentDNANode);

            currentDNANode = beforeDNANode->next;
        }

        currentDNAChain = currentDNAChain->next;
    }

    // переносим элементы из mapOfChains в _dnaStorage
    addNodesToDNAStorageFormMapOfNodeChains();
}

void DNARepairer::printDNAStorage()
{
    NodeDNAChain* currentDNAChain = _dnaStorage.getPreHead()->next;
    while(currentDNAChain != nullptr)                           // проходимся по цепочкам
    {
        NodeDNA* currentDNAElement = currentDNAChain->value.getPreHead()->next;
        while(currentDNAElement != nullptr)                     // проходимся по DNA элементам
        {
            std::cout << currentDNAElement->value << "  ";      // выводим DNA элементы через пробел

            currentDNAElement = currentDNAElement->next;
        }
        std::cout << std::endl;                                 // разделяем цепочки переводом строки строки

        currentDNAChain = currentDNAChain->next;
    }
}

void DNARepairer::readFile(const std::string& filename)
{
    std::ifstream inputFile;                                        // Открывает файл с именем filename для чтения, если это возможно
    inputFile.open(filename, std::ifstream::in);                    // если невозможно, выкидывает исключение
    if(!inputFile.is_open())
        throw std::runtime_error("Could not open file");

    NodeDNAChain* currentNodeOfDNAChain = _dnaStorage.getPreHead();
    while(inputFile.good()) {
        std::string line;
        std::getline(inputFile, line);
        if(line ==
           "")                                                      // считываем строку, и если она пустая переходим к следующей строке
            continue;

        std::istringstream lineIterator(line);                              // проходимся по строкам файла

        NodeDNAChain* nextNodeOfDNAChain;
        try {
            nextNodeOfDNAChain = new NodeDNAChain();
        } catch(std::bad_alloc e) {
            std::cout << e.what();
            exit(EXIT_FAILURE);
        }

        std::string stringOfDNAElement;
        while(lineIterator
                >> stringOfDNAElement)                               // проходимся по строке line и заполняем _dnaStorage DNAElement-ами
        {
            DNAElement el = DNAElement(stringOfDNAElement);
            nextNodeOfDNAChain->value.addElementToEnd(el);
        }

        currentNodeOfDNAChain->next = nextNodeOfDNAChain;
        currentNodeOfDNAChain = nextNodeOfDNAChain;
    }
}


DNARepairer::ListOfDNAChains& DNARepairer::getDNAStorage()
{
    return _dnaStorage;
}
