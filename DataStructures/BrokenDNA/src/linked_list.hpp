#include <stdexcept>

namespace xi {

    template<typename T>
    Node<T>::Node(T val, Node* nxt)
    {
        value = val;
        next = nxt;
    }


    template<typename T>
    LinkedList<T>::LinkedList()
    {
        try {
            _preHead = new Node<T>();
        } catch(std::bad_alloc e) {
            std::cout << e.what();
            exit(EXIT_FAILURE);
        }
    }


    template<typename T>
    LinkedList<T>::LinkedList(const LinkedList <T>& obj)
    {
        try {
            _preHead = new Node<T>();
        } catch(std::bad_alloc e) {
            std::cout << e.what();
            exit(EXIT_FAILURE);
        }

        Node<T>* currentNode;
        Node<T>* nextNode = _preHead;

        Node<T>* objCurrentNode = const_cast<LinkedList<T>&>(obj).getPreHead()->next;           // итератор по копируему объекту

        while(objCurrentNode != nullptr) {
            currentNode = nextNode;

            try {
                nextNode = new Node<T>(objCurrentNode->value);          // создаем новый узел
            } catch(std::bad_alloc e) {
                std::cout << e.what();
                exit(EXIT_FAILURE);
            }

            currentNode->next = nextNode;                           // присоединяем созданный узел с концом

            objCurrentNode = objCurrentNode->next;
        }
    }


    template<typename T>
    LinkedList <T>& LinkedList<T>::operator=(const LinkedList <T>& obj)
    {
        LinkedList<T> copy = LinkedList<T>(obj);
        std::swap(copy._preHead, _preHead);                         // меняем местами _preHead-ы

        return *this;                                               // удаляется объект copy и возвращается ссылка на текущий объект
    }


    template<typename T>
    LinkedList<T>::~LinkedList()
    {
        deleteFrom(_preHead);                               //удаляем все узлы, включая _preHead 
    }


    template<typename T>
    Node <T>* LinkedList<T>::getPreHead()
    {
        return _preHead;
    }


    template<typename T>
    T& LinkedList<T>::operator[](int i)
    {
        if(i < 0)                                              // если индекс меньше чем 0 выбрасывается исключение
            throw std::out_of_range("Index out of range");

        Node<T>* currentNode = _preHead;

        for(int j = -1; j < i; j++) {
            currentNode = currentNode->next;

            if(currentNode ==
               nullptr)                          // Если узел с индексом i не существует, выбрасывается исключение
                throw std::out_of_range("Index out of range");
        }

        return currentNode->value;
    }


    template<typename T>
    int LinkedList<T>::size()
    {
        Node<T>* currentNode = _preHead->next;
        int index = 0;                                          //счетчик количества элементов

        while(currentNode != nullptr) {
            currentNode = currentNode->next;
            index++;
        }

        return index;
    }


    template<typename T>
    void LinkedList<T>::addElementToEnd(T& value)
    {
        Node<T>* node;
        try {
            node = new Node<T>(value);                         // создаем новый элемент со значением value
        } catch(std::bad_alloc e) {
            std::cout << e.what();
            exit(EXIT_FAILURE);
        }

        Node<T>* lastNode = getLastNode();                          // находим последний узел в листе
        lastNode->next = node;                                      // добавляем элемент в конец списка
    }


    template<typename T>
    void LinkedList<T>::deleteNodes(Node <T>* pNodeBefore, Node <T>* pNodeLast)
    {
        if(pNodeBefore == nullptr || pNodeBefore->next == nullptr || pNodeLast == nullptr)
            throw std::invalid_argument("Value can not be null");

        Node<T>* pNodeBeforeNext = pNodeBefore->next;

        pNodeBefore->next = pNodeLast->next;                    //
        pNodeLast->next = nullptr;                              // "вырезаем" элементы из прошлого списка

        deleteFrom(pNodeBeforeNext);                          // удаляем элементы с pNodeBefore->next по pNodeLast
    }


    template<typename T>
    void LinkedList<T>::deleteNextNode(Node <T>* pNodeBefore)
    {
        if(pNodeBefore == nullptr || pNodeBefore->next == nullptr)
            throw std::invalid_argument("Value can not be null");

        deleteNodes(pNodeBefore, pNodeBefore->next);            // удаляет элемент pNodeBefore->next из всписка
    }


    template<typename T>
    void LinkedList<T>::moveNodesToEnd(Node <T>* pNodeBefore, Node <T>* pNodeLast)
    {
        if(pNodeBefore == nullptr || pNodeBefore->next == nullptr || pNodeLast == nullptr)
            throw std::invalid_argument("Value can not be null");

        moveNodesAfter(getLastNode(), pNodeBefore,
                       pNodeLast);      // переносит элементы в конец текущего списка (ставит после последнего элемента)
    }


    template<typename T>
    void LinkedList<T>::moveNodeToEnd(Node <T>* pNodeBefore)
    {
        if(pNodeBefore == nullptr || pNodeBefore->next == nullptr)
            throw std::invalid_argument("Value can not be null");

        moveNodesToEnd(pNodeBefore,
                       pNodeBefore->next);                     // ставят узел pNodeBefore->next в конец списка
    }


    template<typename T>
    void LinkedList<T>::moveNodesAfter(Node <T>* pNode, Node <T>* pNodeBefore, Node <T>* pNodeLast)
    {
        if(pNode == nullptr || pNodeBefore == nullptr || pNodeBefore->next == nullptr || pNodeLast == nullptr)
            throw std::invalid_argument("Value can not be null");

        Node<T>* pNodeNext = pNode->next;                                   // сохраняем ссылку на следующий элемент после pNext

        pNode->next = pNodeBefore->next;                                    // вставляем ноды в левую часть новой цепочки
        pNodeBefore->next = pNodeLast->next;                                // вырезаем ноды из старой цепочки
        pNodeLast->next = pNodeNext;                                        // вставляем ноды в правую часть новой цепочки
    }


    template<typename T>
    void LinkedList<T>::moveNodeAfter(Node <T>* pNode, Node <T>* pNodeBefore)
    {
        if(pNode == nullptr || pNodeBefore == nullptr || pNodeBefore->next == nullptr)
            throw std::invalid_argument("Value can not be null");

        moveNodesAfter(pNode, pNodeBefore, pNodeBefore->next);     // переносим узел pNodeBefore->next после узла pNode
    }


    /// Удаляет из списка все узлы начиная с \c node
    template<typename T>
    void LinkedList<T>::deleteFrom(Node <T>* node)
    {
        Node<T>* nextNode;

        for(; node != nullptr; node = nextNode) {
            nextNode = node->next;
            delete node;
        }
    }


    template<typename T>
    Node <T>* LinkedList<T>::getLastNode()
    {
        Node<T>* currentNode;
        Node<T>* nextNode = _preHead;

        while(nextNode != nullptr) {
            currentNode = nextNode;
            nextNode = currentNode->next;
        }

        return currentNode;
    }


} // namespace xi