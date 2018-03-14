#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

class Huffman
{
    struct Element
    {
        Element()
        {
            value = -1;
            id = -1;
        }

        Element(int value, int id, int index)
        {
            this->value = value;
            indexes.push_back(id);
            this->id = id;
        }

        Element& concat(const Element& obj, int id)
        {
            this->value += obj.value;
            this->id = id;
            indexes.insert(indexes.end(), obj.indexes.begin(), obj.indexes.end());

            return *this;
        }

        struct less
        {
            bool operator()(const Element& first, const Element& second)
            {
                if(first.value == second.value)
                    return first.id < second.id;
                return first.value > second.value;
            }
        };

        int value;
        vector<int> indexes;
        int id;
    };

public:

    // зупскает алгоритм (после того как были добавлены все элементы)
    void build()
    {
        Element a, b;
        while(_pq.size() > 1)
        {
            //Достаем минимальный элемент
            a = _pq.top();
            _pq.pop();

            //Достаем минимальный элемент
            b = _pq.top();
            _pq.pop();

            //записываем код для символа
            vector<int>::iterator it = a.indexes.begin();
            for(; it != a.indexes.end(); ++it)
                _codes[*it] = '0' + _codes[*it];

            //записываем код для символа
            it = b.indexes.begin();
            for(; it != b.indexes.end(); ++it)
                _codes[*it] = '1' + _codes[*it];

            //Суммируем элементы и кладем их в priority queue
            _pq.push(a.concat(b, _free_id++));
        }
    }

    // добовляет елемент в список (дерево, все зависит от реализации)
    void addChance (int chance)
    {
        _codes.emplace_back("");
        _pq.push(Element(chance, _free_id, _free_id));
        ++_free_id;
    }

    string get (int i)
    {
        return _codes[i];
    }

private:

    //дерево частоты символов
    priority_queue<Element, vector<Element>, Element::less> _pq;

    //коллекция кодов
    vector<string> _codes;

    //незанятый индекс
    int _free_id = 0;
};

int main() {

    int n;
    Huffman * huff = new Huffman();
    fstream fin;
    fin.open("input.txt",ios::in);
    if(fin.is_open()) {
        fin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            fin >> x;
            huff->addChance (x);
        }

        fin.close();

        huff->build();
        fstream fout;
        fout.open("output.txt",ios::out);
        for (int i = 0; i < n; i++){
            fout << huff->get(i) << (i==n-1?"":" ");
        }
        fout.close();
        delete huff;

    }

    return 0;

}
