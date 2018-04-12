#include "bigInt/BigIntegerAlgorithms.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

static BigInteger FactTree(int n) //1
{
    BigInteger a(1);
    for(int i = 2; i <= n; ++i)
        a *= i;
    return a;
}

static BigInteger C(int n, int k)//2
{
    int v = max(n - k, k);
    BigInteger a(1);
    for(int i = v + 1; i <= n; ++i)
        a *= i;
    return a / FactTree(n - v);
}

static BigInteger Pair(int n)//3
{
    BigInteger a(1);
    for(int i = 3; i < n; i += 2)
        a *= i;
    return a;
}

int main(int argc, const char* argv[])
{

    int n, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if(fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        n = N;
        getline(fin, str);
        K = atoi(str.c_str());
        fout << FactTree(N) << endl;
        fout << C(N, K) << endl;
        fout << Pair(N) << endl;
        fout.close();
        fin.close();
    }
    return 0;
}
