/*
 * \file
 * \brief реализация класса PriorityQueue
 * \author Чуев Иван БПИ163
 * \date 05.11.2017
 *       Класс представляет собой реализацию очереди с приоритетами.
 *       Создан для использования в класссе RailSystem
 *       Также к этому файлу прилогаются тесты в папке 'tests' файл priority_queue_student_tests.cpp
 */

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <cstddef>      // size_t
#include <functional>   // less
#include <algorithm>    //swap
#include <vector>

template<typename T, typename Comparator = std::less<T>>
class PriorityQueue {
public:

    /** \brief Максимальный размер очереди, если он был не задан в конструкторе */
    static const std::size_t MAX_SIZE = (std::size_t) -1;

public:

    /** \brief Конструктор, создающий очередь с приоритетами */
    PriorityQueue(std::size_t capacity = MAX_SIZE, Comparator comparator = Comparator())
    {
        _compare = comparator;
        _capacity = capacity;
        _binaryHeap = std::vector<T>(0);
    }

public:

    /** \brief Возвращает размер очереди */
    std::size_t size() const
    {
        return _binaryHeap.size();
    }

    /** \brief Определяет, является ли очередь пустой
    * \return true - если очередь пуста
    */
    bool isEmpty()
    {
        return size() == 0;
    }

    /** \brief Определяет, является ли очередь полной
    * \return true - если очередь полна
    */
    bool isFull()
    {
        return size() == _capacity;
    }

    /** \brief Помещает элемент в очередь
    * Если очередь полна, генерируется исключение std::out_of_range
    * \params[in] newElement Добавляемый элемент
    */
    void push(const T& newElement)
    {
        //Если очередь полна, выбрасывается исключение
        if(isFull())
            throw std::out_of_range("Queue is overflow");

        //Добавляется элемент в очередь
        _binaryHeap.push_back(newElement);

        //Элемент в цикле помещается на его место по приоритету
        std::size_t i = size() - 1;
        while(i != 0) {
            std::size_t parentIndex = (i - 1) / 2;                  //Получаем следующий элемент в очереди

            if(_compare(_binaryHeap[parentIndex], _binaryHeap[i]))  //Если приоритет элемента меньше следующего,
                break;                                              //то мы нашли его место и цикл поиска завершается

            std::swap(_binaryHeap[i], _binaryHeap[parentIndex]);    //Если приоритет элемента больше следующего,
            i = parentIndex;                                        //то эл-ты меняются местами
        }
    }

    /** \brief Извлекает элемент из очереди с наибольшим приоритетом
    * Если очередь полна, генерируется исключение std::out_of_range
    * \return Элемент с наибольшим приоритетом
    */
    T pop()
    {
        //Достаем первый элемент из очереди
        T element = top();

        //Если в очереди только один элемент, то возвращаем его
        if(size() == 1) {
            _binaryHeap.pop_back();
            return element;
        }

        //На место первого элемента ставим последний
        _binaryHeap[0] = _binaryHeap[size() - 1];
        _binaryHeap.pop_back();

        //Первый элемент в цикле помещается на его место по приоритету
        std::size_t lChildIndex, rChildIndex, parentIndex = 0, biggestElIndex = 0;
        while(true) {
            lChildIndex = (parentIndex + 1) * 2 - 1;          //Получаем индекс левого ребенка
            rChildIndex = (parentIndex + 1) * 2;              //Получаем индекс правого ребенка

            if(lChildIndex >= size())                         //Если детей нет, то цикл завершается
                break;

            //Определяем ребенка с наибольшим приоритетом
            biggestElIndex =
                    rChildIndex < size() && _compare(_binaryHeap[rChildIndex], _binaryHeap[lChildIndex]) ? rChildIndex
                                                                                                         : lChildIndex;

            if(_compare(_binaryHeap[biggestElIndex],
                        _binaryHeap[parentIndex])) {        //Если ребенок имеетбольший приоритет, чем родитель,
                std::swap(_binaryHeap[biggestElIndex], _binaryHeap[parentIndex]);        //то меняем их местами
                parentIndex = biggestElIndex;
            } else {
                break;                                                                   //Иначе завершаем цикл
            }
        }

        return element;
    }

    /** \brief Возвращает элемент из очереди с наибольшим приоритетом
    * Если очередь полна, генерируется исключение std::out_of_range
    * \return Элемент с наибольшим приоритетом
    */
    T top()
    {
        if(isEmpty())
            throw std::out_of_range("Queue is empty");

        return _binaryHeap[0];
    }


    /** \brief Удаляет первое вхождение элемента element из очереди
    * проходя по бинарной куче слева на право по куче
    */
    void remove(const T& element)
    {
        //Находим первое входжение элемента element
        size_t i = 0;
        for(; i < size(); i++)
            if(_binaryHeap[i] == element)
                break;

        //Если элемент не найден метод завершает работу, ничего не удалив
        if(i == size())
            return;

        //Поднимаем элемент наверх кучи
        while(i != 0) {
            std::size_t parentIndex = (i - 1) / 2;                  //Получаем следующий элемент в очереди

            std::swap(_binaryHeap[i], _binaryHeap[parentIndex]);
            i = parentIndex;
        }

        //Удаляем верхний элемент из кучи
        pop();
    }


protected:

    //Список элементов очереди
    std::vector<T> _binaryHeap;

    //Максимально возможный размер очереди
    std::size_t _capacity;

    //Объект, сравнивающий элементы очереди между собой
    Comparator _compare;

};


#endif //
