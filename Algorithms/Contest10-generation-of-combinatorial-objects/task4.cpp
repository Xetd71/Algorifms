#include "bigint/BigIntegerAlgorithms.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

void getNext(int* p, int n, int k)
{
    int i = k - 1;
    while(p[i] + k - i > n) --i;
    ++p[i];
    for(int j = i + 1; j < k; ++j)
        p[j] = p[j - 1] + 1;
}

static string get_day(int n, int k, int m)
{
    int p[m];
    for(int i = 0; i < m; ++i)
        p[i] = i + 1;
    for(int i = 1; i < k; ++i)
        getNext(p, n, m);
    string res;
    for(int i = 0; i < m - 1; ++i)
        res += to_string(p[i]) + ' ';
    res += to_string(p[m - 1]);
    return res;
}

int main(int argc, const char* argv[])
{
    int M, N, K;
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
        getline(fin, str);
        M = atoi(str.c_str());
        fout << get_day(N, K, M) << endl;
        fout.close();
        fin.close();
    }

    return 0;
}
