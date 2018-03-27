#include "ReadWriter.h"
#include "BubbleSort.h"
#include <algorithm>

using namespace std;

int main(){
    ReadWriter rw;
    int *brr = nullptr;
    int n;
    //Ввод из файла
    n = rw.readInt();
    brr = new int[n];
    rw.readArray(brr, n);
    //Запуск сортировки
    BubbleSort s;
    s.sort(brr, n);
    //Запись в файл
    rw.writeArray(brr, n);
    delete[] brr;
    return 0;
}

void BubbleSort::sort(int* brr, int n)
{
    int lastEx = n - 1, k = 0;
    for(int i = 0; i < n && lastEx; ++i)
    {
        k = 0;
        for(int j = 0; j < lastEx; ++j)
        {
            if(brr[j] > brr[j + 1])
            {
                std::swap(brr[j], brr[j + 1]);
                k = j;
            }
        }
        lastEx = k;
    }
}
