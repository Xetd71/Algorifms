#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <limits.h>
using namespace std;

int bitap_search(const string& text, const string& pattern)
{
    int m = pattern.length();
    if(m == 0)
        return 0;
    if(m > 0x3f)
        return -2;

    unsigned long long pattern_mask[CHAR_MAX + 1];
    for(int i = 0; i <= CHAR_MAX; ++i)
        pattern_mask[i] = LLONG_MAX;
    for(int i = 0; i < m; ++i)
        pattern_mask[pattern[i]] &= ~(1ULL << i);

    unsigned long long R = ~1ULL;
    for(int i = 0, n = text.length(); i < n; ++i)
    {
        R |= pattern_mask[text[i]];
        R <<= 1;
        if((R & (1ULL << m)) == 0)
            return i - m + 1;
    }
    return -1;
}

string findPattern(const string& t, const string& p)
{
    int pos = bitap_search(t, p);
    if (pos == -1)
    return "No Match"; // если нет подстроки
    else if(pos == -2)
        return "Pattern is too long!"; // если паттерн больше 63 символов!
        else
    return "Pattern found at position : " + to_string(pos); // позиция подстроки
}

int main(int argc, char **argv)
{
    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open())
    {
        string N;
        getline(fin,N);
        n = atoi( N.c_str());
        for (int i = 0; i < n; i++)
        {
            string t;
            string p;
            getline(fin,t);
            getline(fin,p);
            fout << findPattern(t, p) << endl;
        }
        fout.close();
        fin.close();
    }
}
