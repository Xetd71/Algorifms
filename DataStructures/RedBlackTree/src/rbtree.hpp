#include <stdexcept>        // std::invalid_argument


namespace xi {


//==============================================================================
// class RBTree::node
//==============================================================================

    template<typename Element, typename Compar>
    RBTree<Element, Compar>::Node::~Node()
    {
        if(_left)
            delete _left;
        if(_right)
            delete _right;
    }


    template<typename Element, typename Compar>
    typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setLeft(Node* lf)
    {
        // предупреждаем повторное присвоение
        if(_left == lf)
            return nullptr;

        // если новый левый — действительный элемент
        if(lf) {
            // если у него был родитель
            if(lf->_parent) {
                // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
                if(lf->_parent->_left == lf)
                    lf->_parent->_left = nullptr;
                else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                    lf->_parent->_right = nullptr;
            }

            // задаем нового родителя
            lf->_parent = this;
        }

        // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
        Node* prevLeft = _left;
        _left = lf;

        if(prevLeft)
            prevLeft->_parent = nullptr;

        return prevLeft;
    }


    template<typename Element, typename Compar>
    typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setRight(Node* rg)
    {
        // предупреждаем повторное присвоение
        if(_right == rg)
            return nullptr;

        // если новый правый — действительный элемент
        if(rg) {
            // если у него был родитель
            if(rg->_parent) {
                // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
                if(rg->_parent->_left == rg)
                    rg->_parent->_left = nullptr;
                else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                    rg->_parent->_right = nullptr;
            }

            // задаем нового родителя
            rg->_parent = this;
        }

        // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
        Node* prevRight = _right;
        _right = rg;

        if(prevRight)
            prevRight->_parent = nullptr;

        return prevRight;
    }


//==============================================================================
// class RBTree
//==============================================================================

    template<typename Element, typename Compar>
    RBTree<Element, Compar>::RBTree()
    {
        _root = nullptr;
        _dumper = nullptr;
    }

    template<typename Element, typename Compar>
    RBTree<Element, Compar>::~RBTree()
    {
        // грохаем пока что всех через корень
        if(_root)
            delete _root;
    }


    template<typename Element, typename Compar>
    void RBTree<Element, Compar>::deleteNode(Node* nd)
    {
        // если переданный узел не существует, просто ничего не делаем, т.к. в вызывающем проверок нет
        if(nd == nullptr)
            return;

        // потомков убьет в деструкторе
        delete nd;
    }


    template<typename Element, typename Compar>
    void RBTree<Element, Compar>::insert(const Element& key)
    {
        // этот метод можно оставить студентам целиком
        Node* newNode = insertNewBstEl(key);

        // отладочное событие
        if(_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_INS, this, newNode);

        rebalance(newNode);

        // отладочное событие
        if(_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_INSERT, this, newNode);

    }


    template<typename Element, typename Compar>
    typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::successor(Node* nd)
    {
        if(nd == nullptr)
            return nullptr;
        else if(nd->_right != nullptr) {
            Node* p = nd->_right;
            while(p->_left != nullptr)
                p = p->_left;
            return p;
        } else {
            Node* p = nd->_parent;
            Node* child = nd;
            while(p != nullptr && child == p->_right) {
                child = p;
                p = p->_parent;
            }
            return p;
        }
    }

    template<typename Element, typename Compar>
    void RBTree<Element, Compar>::fixUpAfterDeletion(Node* x)
    {
        while(x != _root && getColor(x) == BLACK) {
            if(x == getLeft(getParent(x))) {
                Node* sibling = getRight(getParent(x));

                if(getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(getParent(x), RED);
                    rotLeft(getParent(x));
                    sibling = getRight(getParent(x));
                }

                if(getColor(getLeft(sibling)) == BLACK && getColor(getRight((sibling))) == BLACK) {
                    setColor(sibling, RED);
                    x = getParent(x);
                } else {
                    if(getColor(getRight(sibling)) == BLACK) {
                        setColor(getLeft(sibling), BLACK);
                        setColor(sibling, RED);
                        rotRight(sibling);
                        sibling = getRight(getParent(x));
                    }
                    setColor(sibling, getColor(getParent(x)));
                    setColor(getParent(x), BLACK);
                    setColor(getRight(sibling), BLACK);
                    rotLeft(getParent(x));
                    x = _root;
                }
            } else {
                Node* sibling = getLeft(getParent(x));

                if(getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(getParent(x), RED);
                    rotRight(getParent(x));
                    sibling = getLeft(getParent(x));
                }

                if(getColor(getRight(sibling)) == BLACK && getColor(getLeft(sibling)) == BLACK) {
                    setColor(sibling, RED);
                    x = getParent(x);
                } else {
                    if(getColor(getLeft(sibling)) == BLACK) {
                        setColor(getRight(sibling), BLACK);
                        setColor(sibling, RED);
                        rotLeft(sibling);
                        sibling = getLeft(getParent(x));
                    }
                    setColor(sibling, getColor(getParent(x)));
                    setColor(getParent(x), BLACK);
                    setColor(getLeft(sibling), BLACK);
                    rotRight(getParent(x));
                    x = _root;
                }
            }

        }

        setColor(x, BLACK);
    }

    template<typename Element, typename Compar>
    void RBTree<Element, Compar>::remove(const Element& key)
    {
        Node* cNode = _root;
        while(cNode != nullptr) {
            if(_compar(key, cNode->getKey()) == _compar(cNode->getKey(), key))
                break;

            cNode = _compar(key, cNode->getKey()) ? cNode->_left : cNode->_right;
        }

        if(cNode == nullptr)
            return;

        if(cNode->_left != nullptr && cNode->_right != nullptr) {
            Node* s = successor(cNode);
            cNode->_key = s->_key;
            cNode = s;
        }

        Node* replacement = cNode->_left != nullptr ? cNode->_left : cNode->_right;

        if(replacement != nullptr) {
            replacement->_parent = cNode->_parent;
            if(cNode->_parent == nullptr)
                _root = replacement;
            else if(cNode->isLeftChild())
                cNode->_parent->_left = replacement;
            else
                cNode->_parent->_right = replacement;

            cNode->_left = nullptr;
            cNode->_right = nullptr;
            cNode->_parent = nullptr;

            // отладочное событие
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_REMOVE, this, cNode);

            if(cNode->_color == BLACK)
                fixUpAfterDeletion(replacement);

            // отладочное событие
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_REMOVE, this, cNode);
        } else if(cNode->_parent == nullptr) {
            // отладочное событие
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_REMOVE, this, cNode);

            _root = nullptr;
        } else {
            // отладочное событие
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_REMOVE, this, cNode);

            if(cNode->_color == BLACK)
                fixUpAfterDeletion(cNode);

            if(cNode->_parent != nullptr) {
                if(cNode->isLeftChild())
                    cNode->_parent->_left = nullptr;
                else if(cNode->isRightChild())
                    cNode->_parent->_right = nullptr;
                cNode->_parent = nullptr;
            }

            // отладочное событие
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_REMOVE, this, cNode);
        }

        delete cNode;
    }


    template<typename Element, typename Compar>
    const typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::find(const Element& key)
    {
        Node* cNode = _root;
        while(cNode != nullptr) {
            if(_compar(key, cNode->getKey()) == _compar(cNode->getKey(), key))
                return cNode;

            cNode = _compar(key, cNode->getKey()) ? cNode->_left : cNode->_right;
        }

        return nullptr;
    }

    template<typename Element, typename Compar>
    typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::insertNewBstEl(const Element& key)
    {
        Node* prevNode = nullptr;
        Node* cNode = _root;
        while(cNode != nullptr) {
            if(_compar(key, cNode->getKey()) == _compar(cNode->getKey(), key))
                throw std::invalid_argument("Given key already exist");

            prevNode = cNode;
            cNode = _compar(key, cNode->getKey()) ? cNode->_left : cNode->_right;
        }

        Node* newNode = new Node(key, nullptr, nullptr, prevNode, RED);
        if(prevNode != nullptr) {
            if(_compar(newNode->_key, prevNode->_key))
                prevNode->_left = newNode;
            else
                prevNode->_right = newNode;
        } else {
            _root = newNode;
        }

        return newNode;
    }


    template<typename Element, typename Compar>
    typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::rebalanceDUG(Node* nd)
    {
        // попадание в этот метод уже означает, что папа есть (а вот про дедушку пока не известно)

        // определяем папу, дедушку и дядю
        Node* parent = nd->_parent;
        Node* grandpa = parent->_parent;
        Node* uncle = nullptr;
        if(grandpa == nullptr)
            uncle = nullptr;
        else
            uncle = parent->isLeftChild() ? grandpa->_right : grandpa->_left;

        // если дядя такой же красный, как сам нод и его папа
        if(uncle != nullptr && uncle->isRed()) {
            // дядю и папу красим в черное, а дедушку — в коммунистические цвета
            parent->_color = BLACK;
            uncle->_color = BLACK;
            grandpa->_color = RED;

            // отладочное событие
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1, this, nd);

            // теперь чередование цветов "узел-папа-дедушка-дядя" — К-Ч-К-Ч, но надо разобраться, что там
            // с дедушкой и его предками, поэтому продолжим с дедушкой
            rebalance(grandpa);
        } else {
            // дядя черный
            // смотрим, является ли узел "правильно-правым" у папочки
            if(nd->isRightChild() && parent->isLeftChild()) {
                rotLeft(parent);
                nd = nd->_left;
            } else if(nd->isLeftChild() && parent->isRightChild()) {
                rotRight(parent);
                nd = nd->_right;
            }

            parent = nd->_parent;
            grandpa = parent->_parent;

            // Красим отца в черный
            parent->_color = BLACK;
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D, this, nd);

            // Красим деда в красный
            grandpa->_color = RED;
            if(_dumper)
                _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3G, this, nd);

            // Делаем перебалансировку делева
            if(nd->isLeftChild() && parent->isLeftChild())
                rotRight(grandpa);
            else
                rotLeft(grandpa);
        }

        return nd;
    }


    template<typename Element, typename Compar>
    void RBTree<Element, Compar>::rebalance(Node* nd)
    {
        if(nd->_parent == nullptr) {
            nd->_color = BLACK;
            _root = nd;
            return;
        }

        // если папа черный, то дерево уже является сбалансированным
        if(nd->_parent->_color == BLACK)
            return;

        rebalanceDUG(nd);
    }


    template<typename Element, typename Compar>
    void RBTree<Element, Compar>::rotLeft(typename RBTree<Element, Compar>::Node* nd)
    {
        if(nd == nullptr)
            return;

        Node* r = nd->_right;
        if(r == nullptr)
            throw std::invalid_argument("Can't rotate left since the right child is nil");

        Node* parent = nd->_parent;
        r->_parent = parent;
        if(parent != nullptr) {
            if(nd->isLeftChild())
                parent->_left = r;
            else
                parent->_right = r;
        } else {
            _root = r;
        }

        nd->_right = r->_left;
        if(r->_left != nullptr)
            r->_left->_parent = nd;

        nd->_parent = r;
        r->_left = nd;

        // отладочное событие
        if(_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_LROT, this, nd);
    }


    template<typename Element, typename Compar>
    void RBTree<Element, Compar>::rotRight(typename RBTree<Element, Compar>::Node* nd)
    {
        if(nd == nullptr)
            return;

        Node* l = nd->_left;
        if(l == nullptr)
            throw std::invalid_argument("Can't rotate right since the left child is nil");

        Node* parent = nd->_parent;
        l->_parent = parent;
        if(parent != nullptr) {
            if(nd->isLeftChild())
                parent->_left = l;
            else
                parent->_right = l;
        } else {
            _root = l;
        }

        nd->_left = l->_right;
        if(l->_right != nullptr)
            l->_right->_parent = nd;

        nd->_parent = l;
        l->_right = nd;

        // отладочное событие
        if(_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RROT, this, nd);
    }


} // namespace xi

