#include "ReadWriter.h"
#include "MergeSort.h"

using namespace std;

int main()
{
    ReadWriter rw;

    int *brr = nullptr;
    int length;

    //Read length from file
    length = rw.readInt();

    brr = new int[length];
    rw.readArray(brr, length);

    //Start sorting
    MergeSort s;

    s.sort(brr, length);

    //Write answer to file
    rw.writeArray(brr, length);

    delete[] brr;

    return 0;
}

//Описание методов на английском языке имеется в классе MergeSort, в файле MergeSort.h
//Задача реализовать методы, можно добавлять любые свои методы
void MergeSort::sort(int *arr, int length)
{
    divide_and_merge(arr, 0, length - 1);
}


void MergeSort::merge(int* arr, int left, int middle, int right)
{
    int r = right - left, m = middle - left;
    int* arr2 = new int[r + 1];
    for(int i = 0; i < r + 1; ++i)
        arr2[i] = arr[left + i];

    int p1 = 0, p2 = m + 1;
    for(int i = 0; i <= r; ++i)
        arr[i + left] = arr2[p1 > m || (p2 <= r && arr2[p1] > arr2[p2]) ? p2++ : p1++];

    delete[] arr2;
}


void MergeSort::divide_and_merge(int* arr, int left, int right)
{
    if(left >= right)
        return;

    int middle = (left + right) / 2;
    divide_and_merge(arr, left, middle);
    divide_and_merge(arr, middle + 1, right);
    merge(arr, left, middle, right);
}
