#include <fstream>
#include <algorithm>    //swap
using namespace std;

void qSort(int* left, int* right)
{
    int* i = left;
    int* j = right;
    int x = *((right - left) / 2 + left);
    do {
        for(; *i < x; ++i);
        for(; *j > x; --j);
        if(i <= j)
            swap(*i++, *j--);
    } while(i <= j);
    if(left < j)
        qSort(left, j);
    if(i < right)
        qSort(i, right);
}

void quickSort(int *numbers, int array_size)
{
    // сортируем массив
    qSort(numbers, numbers + array_size - 1);
}

int main()
{
    int *brr;
    int n;

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        brr = new int[n];
        for (int i = 0; i < n; i++)
            fin >> brr[i];

        fin.close();
    }
    quickSort(brr, n);
    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < n; i++)
        fout << brr[i] << " ";

    fout.close();
    delete[] brr;
    return 0;
}