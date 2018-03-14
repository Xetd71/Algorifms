#include <stdexcept>
#include <algorithm>    //swap


//==============================================================================
// class BidiList<T>::Node
//==============================================================================


template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::Node::insertAfterInternal(Node *insNode)
{
    insertAfterInternal(insNode, insNode);

    return insNode;                             // возвращаем вставленный элемент
}


template<typename T>
void BidiLinkedList<T>::Node::insertAfterInternal(Node *beg, Node *end)
{
    Node *afterNode = this->_next;              // запоминаем узел, после которого вставлем insNode

    this->_next = beg;                          // соединяем this с beg
    if(beg != nullptr)
        beg->_prev = this;                      // соединяем beg с this

    end->_next = afterNode;                     // соединяем end с afterNode
    if(afterNode != nullptr)
        afterNode->_prev = end;                 // соединяем afterNode c beg
}

//==============================================================================
// class BidiList<T>
//==============================================================================

template<typename T>
BidiLinkedList<T>::BidiLinkedList(const BidiLinkedList<T> &obj)
{
    _head = nullptr;                        //
    _tail = nullptr;                        // задаем нулевыми значениями

    std::size_t size = 0;
    // добавляем элементы в список, в процессе подсчитывая размер
    for(Node *cNode = obj._head; cNode != nullptr; cNode = cNode->_next) {
        appendEl(cNode->_val);
        size++;
    }
    _size = size;
}


template<typename T>
BidiLinkedList<T> &BidiLinkedList<T>::operator=(const BidiLinkedList<T> &obj)
{
    BidiLinkedList<T> temp(obj);            // создаем копию obj
    swap(*this, temp);                      // меняем содержимое temp и *this

    return *this;                           // удаляем 'temp' and и возвращаем скопированный объект
}


template<typename T>
void swap(BidiLinkedList<T> &first, BidiLinkedList<T> &second)
{
    std::swap(first._head, second._head);           // меняем _head местами
    std::swap(first._tail, second._tail);           // меняем _tail местами
    std::swap(first._size,
              second._size);           // меняем _size местами (не бессмыссленная операция если хотябы один из _size задан)
}


template<typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();                // очищаем содержимое BidiLinkedList
}


template<typename T>
void BidiLinkedList<T>::clear()
{
    Node *nextNode;
    for(Node *node = _head; node != nullptr; node = nextNode) {     // очищаем BidiLinkedList
        nextNode = node->_next;
        delete node;
    }

    _head = nullptr;                //
    _tail = nullptr;                //
    _size = NO_SIZE;                // задаем полям "нулевые" значения
}

template<typename T>
size_t BidiLinkedList<T>::getSize()
{
    if(_size == NO_SIZE)           // считаем размер списка, если это требуется
        calculateSize();

    return _size;                   // возвращаем размер списка
}


template<typename T>
void BidiLinkedList<T>::calculateSize()
{
    _size = 0;
    for(Node *node = _head; node != nullptr; node = node->_next)
        _size++;
}


template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::getLastNode() const
{
    return _tail;                               // последний элемент в списке
}


template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::appendEl(const T &val)
{
    Node *newNode = new Node(val);

    insertNodeAfter(getLastNode(), newNode);     // вставляем newNode в конец

    return newNode;
}


// возможно, этот метод даже не надо изменять
template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::insertNodeAfter(Node *node, Node *insNode)
{
    insertNodesAfter(node, insNode,
                     insNode);       // вставляем в список элементы с insNode по insNode (вставляем insNode)

    return insNode;
}


template<typename T>
void BidiLinkedList<T>::insertNodesAfter(Node *node, Node *beg, Node *end)
{
    // проверка того, что переданные ноды не nullptr
    if(beg == nullptr || end == nullptr)
        throw std::invalid_argument("Inserted node is nullptr");

    // проверка, не содержатся ли ноды в другой цепочке
    if(beg->_prev != nullptr || end->_next != nullptr)
        throw std::invalid_argument("Inserted node has siblings. It seems it isn't free");


    if(node == nullptr)
        node = getLastNode();

    if(node == nullptr) {
        _head = beg;
        _tail = end;
    } else {
        node->insertAfterInternal(beg, end);
        // если нод вставляется в конец, то _tail обновляется
        if(node == _tail)
            _tail = end;
    }

    // указываем _size не заданным
    invalidateSize();
}


// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS


template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::insertNodeBefore(Node *node, Node *insNode)
{
    insertNodesBefore(node, insNode, insNode);

    return insNode;
}


template<typename T>
void BidiLinkedList<T>::insertNodesBefore(Node *node, Node *beg, Node *end)
{
    if(node == nullptr || node == _head) {
        if(_head != nullptr) {                  // Вставляем цепочку перед _head
            end->_next = _head;
            _head->_prev = end;
        } else
            _tail = end;                        // Если _head == nullptr, то запоминаем _tail

        _head = beg;                            // запоминаем первый элемент в листе

        invalidateSize();
    } else {
        insertNodesAfter(node->_prev, beg, end); // вставляем в список после node->_prev элемент insNode
    }
}

#endif // IWANNAGET10POINTS


template<typename T>
void BidiLinkedList<T>::cutNodes(Node *beg, Node *end)
{
    if(beg == nullptr || end == nullptr)                       // проверка, что вырезаемые элементы не nullptr
        throw std::invalid_argument("Cut node is nullptr");

    if(_head == beg) {
        if(end->_next !=
           nullptr)                   // удаляем ссылку на предыдущий элемент у будущего head, если это возможно
            end->_next->_prev = nullptr;

        _head = end->_next;                         // вырезаем элементы
    } else {
        beg->_prev->_next = end->_next;             // вырезаем элементы

        if(end->_next != nullptr)                   // создаем ссылку назад к элементу после end, если он есть
            end->_next->_prev = beg->_prev;
    }


    if(_tail == end)                                // если был вырезан _tail из списка, обновляем _tail
        _tail = beg->_prev;

    beg->_prev = nullptr;                           // убираем связи вырезанной цепочки нодов с элементами листа
    end->_next = nullptr;

    invalidateSize();                               // указываем _size не заданным
}


template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::cutNode(Node *node)
{
    cutNodes(node, node);                       // Вырезаем из листа элементы с node по node (вырезаем элемент node)

    return node;
}


template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::findFirst(Node *startFrom, const T &val)
{
    // Если startFrom, то возвращаем nullptr
    if(startFrom == nullptr)
        return nullptr;

    // находим и возвращаем элемент со значением val
    for(Node *cNode = startFrom; cNode != nullptr; cNode = cNode->_next)
        if(cNode->_val == val)
            return cNode;

    return nullptr;     // not found
}


template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::findLast(Node *startFrom, const T &val)
{
    // Если startFrom, то возвращаем nullptr
    if(startFrom == nullptr)
        return nullptr;

    // находим и возвращаем элемент со значением val
    for(Node *cNode = startFrom; cNode != nullptr; cNode = cNode->_prev)
        if(cNode->_val == val)
            return cNode;

    return nullptr;     // not found
}


template<typename T>
typename BidiLinkedList<T>::Node **BidiLinkedList<T>::findAll(Node *startFrom, const T &val, int &size)
{
    if(!startFrom)
        return nullptr;

    size = 0;
    // список с найденными элементыми, у которых значение равно val
    BidiLinkedList<Node *> listOfFoundNodes;
    // находим все элементы списка со значениеми val и добавляем их в список listOfFoundNodes
    for(Node *cNode = startFrom; cNode != nullptr; cNode = cNode->_next) {
        if(cNode->_val == val) {
            size++;
            listOfFoundNodes.appendEl(cNode);
        }
    }

    // Если не найдено ни одного элемента в листе , у которых значение равно val, возвращается nullptr
    if(size == 0)
        return nullptr;

    // массив с найденными элементами
    Node **res = new Node *[size];
    typename BidiLinkedList<Node *>::Node *cNode = listOfFoundNodes.getHeadNode();
    // копируем элементы из листа listOfFoundNodes в возвращаемый массив
    for(int i = 0; i < size; ++i) {
        res[i] = cNode->getValue();
        cNode = cNode->getNext();
    }

    return res;
}

// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template<typename T>
typename BidiLinkedList<T>::Node **BidiLinkedList<T>::cutAll(Node *startFrom, const T &val, int &size)
{
    // находим элементы со значением val  списке
    Node **foundNodes = findAll(startFrom, val, size);

    // вырезаем найденные элементы из списка
    for(int i = 0; i < size; ++i)
        cutNode(foundNodes[i]);

    // возвращаем найденные элементы
    return foundNodes;
}

#endif // IWANNAGET10POINTS
