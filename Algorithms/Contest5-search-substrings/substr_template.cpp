#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<int> getSubstrings(string t, string p)
{
    int k = p.length();
    int n = k + t.length() + 1;
    string s = p + "\n" + t;
    vector<int> out;
    if(k == 0)
        return out;

    // считаем размеры граней, если встретилась подстрока добавляем ее индекс в out
    int* pi = new int[n];
    pi[0] = 0;
    for(int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while(j > 0 && s[i] != s[j])
            j = pi[j - 1];
        pi[i] = s[i] == s[j] ? ++j : j;
        if(j == k)
            out.push_back(i - 2 * k);
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