/*
 * \file
 * \brief реализация классов SkipList + NodeSkipList
 * \author Чуев Иван БПИ163
 * \date 12.11.2017
 *              Написана реализация класса SkipList
 *              реализованы методы: insert, remove, findLastLessThan, findFirst
 *              Добавлена реализация большой тройки (деструктор, конструктор копирования, оператор "=")
 *              К классу SkipList прилогаются тесты, которые находятся в файле SkipList_Student_Tests.cpp
 */

#include <cstdlib>
#include <stdlib.h>     //rand
#include <cstdlib>      //srand
#include "SkipList.h"

//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

template<class Value, class Key, int numLevels>
void NodeSkipList<Value, Key, numLevels>::clear(void)
{
    for(int i = 0; i < numLevels; ++i) {
        this->m_nextjump[i] = 0;
    }
    this->m_levelHighest = -1;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
    clear();
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key)
{
    clear();

    this->m_key = key;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key, Value value)
{
    clear();

    this->m_key = key;
    this->m_value = value;
}

//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================
template<class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
    m_probability = probability;
    for(int i = 0; i < numLevels; ++i) {
        // Lets use m_pPreHead as a final sentinel element
        this->m_pPreHead->m_nextjump[i] = this->m_pPreHead;
    }
    this->m_pPreHead->m_levelHighest = numLevels - 1;

    srand((unsigned) time(0));           //Для правильного рандома
}

template<class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(const SkipList<Value, Key, numLevels>& obj)
{
    //Копируем вероятность
    this->m_probability = obj.m_probability;

    //массив с элементами, уровни которых крайние с лева (нужно для корректного копирования уровней поэлементно)
    //Его не надо будет удалять, так как массив статический
    NodeSkipList<Value, Key, numLevels>* lastLevelNodes[numLevels];

    //Инициализируем массив lastLevelNodes элементами this->m_pPreHead и создаем массив m_nextjump для this->m_pPreHead
    for(int i = 0; i < numLevels; ++i) {
        this->m_pPreHead->m_nextjump[i] = this->m_pPreHead;
        lastLevelNodes[i] = this->m_pPreHead;
    }
    this->m_pPreHead->m_levelHighest = numLevels - 1;

    //Копируем элементы списка
    NodeSkipList<Value, Key, numLevels>* thisNode = this->m_pPreHead;
    for(NodeSkipList<Value, Key, numLevels>* objNode = obj.m_pPreHead->m_next;
        objNode != obj.m_pPreHead; objNode = objNode->m_next, thisNode = thisNode->m_next) {
        //Создаем новый элемент, для добавления в список
        NodeSkipList<Value, Key, numLevels>* newNode = new NodeSkipList<Value, Key, numLevels>(objNode->m_key,
                                                                                               objNode->m_value);
        newNode->m_levelHighest = objNode->m_levelHighest;

        //Добавляем элемент в список
        thisNode->m_next = newNode;
        newNode->m_next = this->m_pPreHead;

        //Связывем уровни с новым элементом
        for(int i = 0; i <= objNode->m_levelHighest; ++i) {
            lastLevelNodes[i]->m_nextjump[i] = newNode;
            lastLevelNodes[i] = newNode;
            newNode->m_nextjump[i] = this->m_pPreHead;
        }
    }

    srand((unsigned) time(0));           //Для правильного рандома
}

template<class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>& SkipList<Value, Key, numLevels>::operator=(const SkipList<Value, Key, numLevels>& obj)
{
    //Копируем obj в объект copy
    SkipList<Value, Key, numLevels> copy = SkipList<Value, Key, numLevels>(obj);

    //меняем содержимое this и copy
    double thisProbability = this->m_probability;
    this->m_probability = copy.m_probability;
    copy.m_probability = thisProbability;

    NodeSkipList<Value, Key, numLevels>* thisPreHead = this->m_pPreHead;
    this->m_pPreHead = copy.m_pPreHead;
    copy.m_pPreHead = thisPreHead;

    //возвращаем измененный объект
    return *this;
}

template<class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::~SkipList()
{
    NodeSkipList<Value, Key, numLevels>* node;
    NodeSkipList<Value, Key, numLevels>* nextNode = this->m_pPreHead->m_next;

    //Удаляем элементы списка без this->m_pPreHead
    while(nextNode != this->m_pPreHead) {
        node = nextNode;
        nextNode = nextNode->m_next;

        delete node;
    }

    //Удаляем this->m_pPreHead
    delete this->m_pPreHead;
}

template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key)
{
    //Определяем колиичество уровней элемента
    int level = -1;
    while(((double) rand() / RAND_MAX) < m_probability)
        //Чтобы среднее колличество элементов на уровне numLevels - 1 было в 2 раза больше чем на  numLevels - 2
        level = (level + 1) % numLevels;

    //Создаем новый элемент списка
    NodeSkipList<Value, Key, numLevels>* insNode = new NodeSkipList<Value, Key, numLevels>();
    insNode->m_levelHighest = level;
    insNode->m_value = value;
    insNode->m_key = key;

    //Проходимся по уровням с максимального по минимальный и ищем промежуток, в который нужно вставить элемент
    NodeSkipList<Value, Key, numLevels>* cNode = this->m_pPreHead;
    for(int i = cNode->m_levelHighest; i >= 0; --i) {
        //Проходимся по уровням
        while(cNode->m_nextjump[i] != this->m_pPreHead && cNode->m_nextjump[i]->m_key < key)
            cNode = cNode->m_nextjump[i];

        //Обновляем уровни для списка (нужно для корректного добавления элемента в список)
        if(i <= level) {
            insNode->m_nextjump[i] = cNode->m_nextjump[i];
            cNode->m_nextjump[i] = insNode;
        }
    }

    //Находим точное место, куда надо вставить элемент с ключем key
    while(cNode->m_next != this->m_pPreHead && cNode->m_next->m_key < key)
        cNode = cNode->m_next;

    //Вставляем элемент в его позицию в списке
    insNode->m_next = cNode->m_next;
    cNode->m_next = insNode;
}

template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode* node)
{
    //Если элемент nullptr или m_pPreHead выбрасывается исключение
    if(node == nullptr || node == this->m_pPreHead)
        throw std::invalid_argument("Node doesn't belong to list!");

    //Проходимся по уровням с максимального по минимальный и ищем промежуток, в котором может находиться элемент
    NodeSkipList<Value, Key, numLevels>* cNode = this->m_pPreHead;
    for(int i = cNode->m_levelHighest; i >= 0; --i) {
        //Проходимся по уровням
        while(cNode->m_nextjump[i] != this->m_pPreHead && cNode->m_nextjump[i]->m_key < node->m_key)
            cNode = cNode->m_nextjump[i];

        //Обновляем уровни для списка (нужно для корректного удаления элемента из списка)
        if(cNode->m_nextjump[i] == node)
            cNode->m_nextjump[i] = cNode->m_nextjump[i]->m_nextjump[i];
    }

    //Находим точное место, где находится элемент с ключем key
    while(cNode->m_next != this->m_pPreHead && cNode->m_next->m_key < node->m_key)
        cNode = cNode->m_next;

    //Если элемент не найден, выбрасывается исключение
    if(cNode->m_next != node)
        throw std::invalid_argument("Node doesn't belong to list!");

    //Удаляем элемент из списка
    NodeSkipList<Value, Key, numLevels>* removedNode = cNode->m_next;
    cNode->m_next = removedNode->m_next;
    delete removedNode;
}

template<class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode* SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const
{
    //Проходимся по уровням с максимального по минимальный и ищем промежуток, в котором может находиться элемент
    NodeSkipList<Value, Key, numLevels>* cNode = this->m_pPreHead;
    for(int i = cNode->m_levelHighest; i >= 0; --i)
        while(cNode->m_nextjump[i] != this->m_pPreHead && cNode->m_nextjump[i]->m_key < key)
            cNode = cNode->m_nextjump[i];

    //Находим точное место, где находится элемент
    while(cNode->m_next != this->m_pPreHead && cNode->m_next->m_key < key)
        cNode = cNode->m_next;

    //Возвращаем найденный элемент
    return cNode;
}

template<class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode* SkipList<Value, Key, numLevels>::findFirst(Key key) const
{
    //Проходимся по уровням с максимального по минимальный и ищем промежуток, в котором может находиться элемент
    NodeSkipList<Value, Key, numLevels>* cNode = this->m_pPreHead;
    for(int i = cNode->m_levelHighest; i >= 0; --i) {
        //Если элемент найден, то он возвращается
        if(cNode->m_nextjump[i]->m_key == key && cNode->m_nextjump[i] != this->m_pPreHead)
            return cNode->m_nextjump[i];

        //Проходимся по уровням
        while(cNode->m_nextjump[i] != this->m_pPreHead && cNode->m_nextjump[i]->m_key < key) //preHead
            cNode = cNode->m_nextjump[i];
    }

    //Находим точное место, где находится элемент
    while(cNode->m_next != this->m_pPreHead && cNode->m_next->m_key < key)
        cNode = cNode->m_next;

    //Возвращается найденный элемент, если элемент не найден, возвращается nullptr
    return cNode->m_next->m_key == key ? cNode->m_next : nullptr;
}

// Put your code here

//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
