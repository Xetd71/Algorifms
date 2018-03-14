#ifndef BROKENDNA_LINKEDLIST_H_
#define BROKENDNA_LINKEDLIST_H_


/// Так как классы связанного списка являются типами общего назначения и подходят
/// для решения не только частной задачи с починкой ДНК, мы их заключаем в пространство
/// имен нашей рабочей группы, чтобы снизить вероятность конфликта имен при включении
/// этих типов в другие проекты.
namespace xi {


/** \brief Узел связного списка.
 *
 *  Класс узла является оберткой для элементов типа \c T, которые хранятся в списке.
 */
    template<class T>
    class Node {
    public:
        /// Конструктор
        Node() : next(nullptr) {}

        ///Конструктор инициализирующий \a значением элемента
        Node(T val, Node* nxt = nullptr);

    public:
        /// Собственно значение элемента.
        T value;

        /// Указатель на узел-обертку следующего элемента
        Node* next;
    }; // class Node




/** \brief Шаблон класса связного списка.
 *
 *  Односвязный список. Особенность такого списка — практически все операции с «текущим элементом»
 *  выполняются через указатель на его предшественника.
 */
    template<class T>
    class LinkedList {

    public:
        /// Конструктор по умолчанию
        LinkedList();

        /// Конструктор копирования
        LinkedList(const LinkedList<T>& obj);

        /// Оператор присваивания
        LinkedList<T>& operator=(const LinkedList<T>& obj);

        /// Деструктор
        ~LinkedList();


    public:
        /// Возвращаем псевдо-нулевой элемент PreHead
        Node<T>* getPreHead();

        /// Возвращает элемент по индексу. Операция дорогая, сложность — O(n)
        /// Нумерация элементов начинается с нуля
        T& operator[](int i);


        /// Возвращает размер списка (число элементов). Операция дорогая, сложность — O(n)
        int size();


        /// Создает и добавляет новый узел, несущий значение \c value, в конец текущего списка.
        void addElementToEnd(T& value);

        /// Удаляет все узлы в диапазоне \c pNodeBefore->next ... \с pNodeLast (включительно).
        void deleteNodes(Node<T>* pNodeBefore, Node<T>* pNodeLast);

        /// Удаляет узел \c pNodeBefore->next.
        void deleteNextNode(Node<T>* pNodeBefore);

        /// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в конец текущего списка.
        /// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
        void moveNodesToEnd(Node<T>* pNodeBefore, Node<T>* pNodeLast);

        /// Перемещает узел pNodeBefore->next из другого списка в конец текущего списка.
        /// После перемещения из другого списка этот узел исключается.
        void moveNodeToEnd(Node<T>* pNodeBefore);

        /// Перемещает узлы \c pNodeBefore->next ... \c pNodeLast другого списка в текущий список
        /// после узла \c pNode.
        /// Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
        void moveNodesAfter(Node<T>* pNode, Node<T>* pNodeBefore, Node<T>* pNodeLast);

        /// Перемещает узел pNodeBefore->next из другого списка в текущий список после узла pNode.
        /// После перемещения из другого списка этот узел исключается.
        void moveNodeAfter(Node<T>* pNode, Node<T>* pNodeBefore);

        /// Возвращает последний узел у списка. Операция дорогая, сложность — O(n)
        Node<T>* getLastNode();

    private:

        /// Удаляет из списка все узлы начиная с \c node
        void deleteFrom(Node<T>* node);


    protected:

        /// Вспомогательный элемент — псевдонулевой элемент списка.
        /// Тип \c T должен поддерживать конструктор по умолчанию.
        Node<T>* _preHead;
        // Вспомогательный элемент

    };

} // namespace xi

#include "linked_list.hpp"

#endif // BROKENDNA_LINKEDLIST_H_

