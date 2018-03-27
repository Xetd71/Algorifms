#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

class ShannonFano
{
public:

    ShannonFano()
    {
        _total = 0;
    }

    ~ShannonFano()
    {
        delete[] _codes;
    }

    void fillCodes(int* left, int* right, int total)
    {
        //Находим медиану
        int* m = left;
        int leftSum = *left;
        int* next = left + 1;
        while(abs(leftSum + *next - (total - leftSum - *next)) < abs(leftSum - (total - leftSum)))
        {
            leftSum += *next;
            m = next;
            ++next;
        }

        int i = (int)(left - _values);
        //Задаем коды для левой части
        for(; i < m + 1 - _values; ++i)
            _codes[i] += '0';
        //Задаем коды для правой части
        for(; i < right + 1 - _values; ++i)
            _codes[i] += '1';

        //Рекурсивно задаем коды
        if(m - left > 0)
            fillCodes(left, m, leftSum);
        if(right - m > 1)
            fillCodes(m + 1, right, total - leftSum);
    }

    // зупскает алгоритм (после того как были добавлены все элементы)
    void build()
    {
        int n = _chances.size();
        _codes = new string[n];
        _values = _chances.data();
        fillCodes(_values, _values + n - 1, _total);
    }

    // добовляет елемент в список (дерево, все зависит от реализации)
    void addChance (int chance)
    {
        _chances.push_back(chance);
        _total += chance;
    }

    // выдает битовый код i символа
    string get (int i)
    {
        return _codes[i];
    }

private:

    vector<int> _chances;
    int* _values;
    string* _codes;
    int _total;

};


int main() {

    int n;
    ShannonFano * shf = new ShannonFano();
    fstream fin;
        fin.open("input.txt",ios::in);
        if(fin.is_open()) {
            fin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                fin >> x;
               shf->addChance (x);
            }
    
            fin.close();
       
        shf->build();
        fstream fout;
        fout.open("output.txt",ios::out);
            for (int i = 0; i < n; i++){
                fout << shf->get(i) << (i==n-1?"":" ");
                }
        fout.close();
        delete shf;
            
        }
  
        return 0;

}

