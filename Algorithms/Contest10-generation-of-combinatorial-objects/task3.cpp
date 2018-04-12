#include "bigint/BigIntegerAlgorithms.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

void getNextAccommodation(int* p, int n, int m, int t, int& j, int k, unordered_set<int> &s)
{
    for(int i = 1; i <= n; ++i)
    {
        if(j == k)
            return;
        if(s.find(i) == s.end())
        {
            s.insert(i);
            p[t] = i;
            if(t < m - 1)
                getNextAccommodation(p, n, m, t + 1, j, k, s);
            else if(++j == k)
                    return;
            s.erase(i);
        }
    }

}

static string get_day(int n, int k, int m)
{
    int p[m];
    unordered_set<int> s;
    int j = 0;
    getNextAccommodation(p, n, m, 0, j, k, s);
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
