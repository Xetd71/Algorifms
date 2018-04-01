#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

vector<int> lis(int* arr, int n)
{
    vector<int> res;
    res.emplace_back(arr[0]);
    //на каждом шаге выбираем первый подходящий зуб пилы
    for(int i = 1; i < n - 1; ++i)
    {
        int el = res.back();
        if((arr[i] > arr[i + 1] && arr[i] > el) || (arr[i] < arr[i + 1] && arr[i] < el))
            res.emplace_back(arr[i]);
    }

    if(arr[n - 1] != res.back())
        res.emplace_back(arr[n - 1]);

    return res;
}

int main()
{
    int len;
    int* arr = nullptr;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if(fin.is_open())
    {
        fin >> len;
        arr = new int[len];
        for(int i = 0; i < len; i++)
            fin >> arr[i];
        fin.close();
    }

    res = lis(arr, len);

    fstream fout;
    fout.open("output.txt", ios::out);
    for(int i = 0; i < res.size(); i++)
        fout << res[i] << " ";
    fout.close();

    return 0;
}