#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

int Wagner_Fischer(const string& s, const string& t)
{
    int lenS = s.length(), lenT = t.length();
    int d[lenS + 1][lenT + 1];

    for(int i = 0; i <= lenT; ++i)
        d[0][i] = i;

    for(int i = 1; i <= lenS; ++i) {
        d[i][0] = i;
        for(int j = 1; j <= lenT; ++j) {
            d[i][j] = min(
                min(
                    d[i - 1][j - 1] + (int)(s[i - 1] != t[j - 1]),
                    d[i - 1][j] + 1
                ),
                d[i][j - 1] + 1
            );
        }
    }

    return d[lenS][lenT];
}

int main(int argc, const char * argv[]) {

    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);
    if(fin.is_open()) {
        string N;
        getline(fin,N);
        n = atoi( N.c_str());
        for (int i = 0; i < n; i++) {
            string s;
            string t;
            getline(fin,s);
            getline(fin,t);
            fout << Wagner_Fischer(s, t) << (i == n-1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }

    return 0;
}