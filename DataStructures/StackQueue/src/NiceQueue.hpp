#include "NiceQueue.h"
#include <algorithm>

template<typename T>
NiceQueue<T>::NiceQueue(size_t capacity)
{
    m_capacity = capacity;                  // задаем вместимость очереди
    // создаем стек входной стек с длинной равной capacity
    // (чтобы обеспечить возможность добавления элементов вплоть до capacity, размер inStack должен быть не меньше capacity)
    inStack = NiceStack<T>(capacity);
    // создаем выходной стек с вместимостью равной inStack.size()
    // (чтобы обеспечить возможность извлечения элементов не нарушая очередь, когда она размером capacity)
    outStack = NiceStack<T>(capacity);
}

template<typename T>
size_t NiceQueue<T>::size() const
{
    // количество элементов в очереди равно сумме колличества элементов в inStack и outStack
    return inStack.size() + outStack.size();
}

template<typename T>
void NiceQueue<T>::enq(T newElement) throw(out_of_range)
{
    // Если размер очереди равен вместимости, то добавить больше элементов нельзя. Возбуждается исключение
    if(m_capacity == size())
        throw std::out_of_range("Queue is overflow");

    inStack.push(newElement);       // добавляем элемент в очередь
}

template<typename T>
T NiceQueue<T>::deq(void) throw(out_of_range)
{
    // Если колличество элементов в очереди равно нулю, то невозно вернуть элемент. Возбуждается исключение
    if(size() == 0)
        throw std::out_of_range("Queue is empty");

    if(outStack.size() == 0)                // Если outStack пуст, то все элементы из inStack перемещаются в outStack
        while(inStack.size() != 0)
            outStack.push(inStack.pop());

    return outStack.pop();                  // Возвращается элемент из outStack
}

template<typename T>
T NiceQueue<T>::getMinimum(void) throw(out_of_range)
{
    return inStack.size() == 0 ? outStack.size() == 0 ? throw std::out_of_range(
            "Queue is empty")                       // Если очередь пуста
                                                      : outStack.getMinimum()                                           // Если inStack пуст
                               : outStack.size() == 0
                                 ? inStack.getMinimum()                                            // Если outStack пуст
                                 : std::min(inStack.getMinimum(),
                                            outStack.getMinimum());          // Если inStack и outStack не пусты
}
