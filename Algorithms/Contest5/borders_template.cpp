#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>

using namespace std;

// считаем наибольшие грани
int* prefixFunction(string s, int n)
{
    int* pi = new int[n];
    pi[0] = 0;
    for(int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while(j > 0 && s[i] != s[j])
            j = pi[j - 1];
        pi[i] = s[i] == s[j] ? ++j : j;
    }
    return pi;
}

string getBorders(string s)
{
    int n = s.length();
    int* pi = prefixFunction(s, n);

    // находим индексы граней строки s
    int i = pi[n - 1], k = -1;
    int* res = new int[i];
    while(i != 0)
    {
        res[++k] = i;
        i = pi[i - 1];
    }

    //записываем результат в строку
    string out;
    for(int j = k; j >= 0; --j)
        out += s.substr(0, res[j]) + "\n";

    delete[] pi;
    delete[] res;
    return out;
}

int main()
{
    string input;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if(fin.is_open()) {
        getline(fin, input);
        fin.close();
    }

    res = getBorders(input);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}