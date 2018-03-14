#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

// считаем наибольшие грани
int* prefixFunction(string s, int n)
{
    int* pi = new int[n];
    pi[0] = 0;
    int j;
    for(int i = 1; i < n; ++i)
    {
        j = pi[i - 1];
        while(j > 0 && s[i] != s[j])
            j = pi[j - 1];
        pi[i] = s[i] == s[j] ? ++j : j;
    }
    return pi;
}

vector<int> getSubstrings(string t, string p)
{
    int n = t.length(), k = p.length(), q = 0;
    vector<int> out;
    if(k == 0)
        return out;
    int* pi = prefixFunction(t, n);

    // находим индексы вхождения строк
    for(int i = 0; i < n; ++i)
    {
        while(q > 0 && p[q] != t[i])
            q = pi[q - 1];
        if(p[q] == t[i])
            ++q;
        if(q == k)
        {
            q = pi[q - 1];
            out.push_back(i - k + 1);
        }
    }

    delete[] pi;
    return out;
}

int main()
{
    string t;
    string p;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if(fin.is_open()) {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    res = getSubstrings(t, p);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res.size() << "\n";
    for(std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}