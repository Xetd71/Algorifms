#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>    //swap
using namespace std;

void qSort(int *numbers, int left, int right)
{
    int i = left, j = right;
    int x = numbers[right];
    do {
        for(; numbers[i] < x; ++i);
        for(; numbers[j] > x; --j);
        if(i <= j)
            swap(numbers[i++], numbers[j--]);
    } while(i <= j);
    if(left < j)
        qSort(numbers, left, j);
    if(i < right)
        qSort(numbers, i, right);
}

void quickSort(int *numbers, int array_size)
{
    srand((unsigned int)(time(0)));
    // перемешиваем массив
    for(int i = 0; i < array_size / 2; ++i)
        swap(numbers[rand() % array_size], numbers[rand() % array_size]);
    // сортируем массив
    qSort(numbers, 0, array_size - 1);
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