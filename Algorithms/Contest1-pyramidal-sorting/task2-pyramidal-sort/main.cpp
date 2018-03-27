#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

inline void heapify(int* heap, int heapSize, int el)
{
    int l, r, largest, parent = el;
    while(true) {
        // Finds indexes of parent children
        l = 2 * parent + 1;
        r = 2 * parent + 2;
        if(l >= heapSize)
            break;

        // Finds the index of the largest element
        largest = r < heapSize && heap[r] > heap[l] ? r : l;
        if(heap[parent] >= heap[largest])
            break;
        swap(heap[parent], heap[largest]);
        parent = largest;
    }
}

void heapSort(int *numbers, int array_size)
{
    // Heap creation
    for(int i = array_size / 2 - 1; i >= 0; --i)
        heapify(numbers, array_size, i);

    // Heap sort
    for(int i = array_size - 1; i >= 0 ; --i) {
        swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
}

//int main() {
//    int *brr;
//    int n;
//
//    fstream fin;
//    fin.open("input.txt",ios::in);
//    if(fin.is_open()) {
//        fin >> n;
//        brr = new int[n];
//        for (int i = 0; i < n; i++) {
//            fin >> brr[i];
//        }
//
//        fin.close();
//    }
//    heapSort(brr, n);
//    fstream fout;
//    fout.open("output.txt",ios::out);
//    for (int i = 0; i < n; i++)
//        fout << brr[i] << " ";
//
//    fout.close();
//    delete[] brr;
//    return 0;
//}
void foo() {
    foo();
}

int main() {
    foo();
    return 0;
}
