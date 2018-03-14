#include "NiceStack.h"
#include <algorithm>

template<typename T>
NiceStack<T>::NiceStack(size_t capacity)
{
    m_capacity = capacity;                              // задаем вместимость стека
    iHead = 0;                                          // указывает на следующий(будущий) элемент в стеке
    storage = vector<TypeElementStack>(capacity);       // вектор, содержащий элементы стека
}


template<typename T>
NiceStack<T>::~NiceStack()
{
    //do nothing            // никакое из полей класса не хранится в куче, следовательно удалять ничего не надо
}


template<typename T>
size_t NiceStack<T>::size() const
{
    return iHead;           // так как iHead указывает на следующий элемент, то он эквивалентен размеру стека
}

template<typename T>
void NiceStack<T>::push(T newElement) throw(out_of_range)
{
    // Если колличество элементов стека равно вместимости, то добавить больше элементов нельзя. Возбуждается исключение
    if(m_capacity == iHead)
        throw std::out_of_range("Stack is overflow");

    // кладем новый элемент стека, высчитывая наименьший после него элемент
    storage[iHead] = TypeElementStack(newElement,
                                      iHead == 0 ? newElement : std::min(storage[iHead - 1].second, newElement));
    iHead++;        // переводим iHead на следующий элемент стека
}

template<typename T>
T NiceStack<T>::pop(void) throw(out_of_range)
{
    // Если в стеке нет элементов, то возвратить ничего нельзя. Возбуждается исключение
    if(iHead == 0)
        throw std::out_of_range("Stack is empty");

    return storage[--iHead].first;      // возращается верхний элемент стека, iHead уменьшается на 1 
}

template<typename T>
T NiceStack<T>::getMinimum(void) throw(out_of_range)
{
    // Если в стеке нет элементов, то и нет минимального числа. Возбуждается исключение
    if(iHead == 0)
        throw std::out_of_range("Stack is empty");

    return storage[iHead -
                   1].second;       // возвращаем наименьший элемент в стеке ниже элемента на самой вершине(наименьший элемент во всем стеке)
}