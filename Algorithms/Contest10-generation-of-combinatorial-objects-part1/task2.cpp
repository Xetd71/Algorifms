#include "bigint/BigIntegerAlgorithms.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void getNextReshuffle(int* p, int n)
{
    int i, j;
    i = j = n - 1;
    while(i > 0 && p[i] < p[i - 1])
        --i;
    while(p[j] < p[i - 1])
        --j;
    swap(p[i - 1], p[j]);
    for(int k = 0, l = (n - i + 1) / 2; k < l; ++k)
        swap(p[i + k], p[n - k - 1]);
}

static string get_day(int n, int k)
{
    int p[n];
    for(int i = 0; i < n; ++i)
        p[i] = i + 1;
    for(int i = 1; i < k; ++i)
        getNextReshuffle(p, n);
    string res;
    for(int i = 0; i < n - 1; ++i)
        res += to_string(p[i]) + ' ';
    res += to_string(p[n - 1]);
    return res;
}

int main(int argc, const char* argv[])
{
    int N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if(fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());

        getline(fin, str);
        K = atoi(str.c_str());
        fout << get_day(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}
