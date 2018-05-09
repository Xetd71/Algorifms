#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

static int __ = []() {
    ios::sync_with_stdio(false);
    return 0;
}();

bool checkPlace(vector<pair<int, int>>& r, int x, int y)
{
    for(auto& el : r)
        if(el.first == x || el.second == y || abs(el.first - x) == abs(el.second - y))
            return false;
    return true;
}

bool findPlaces(vector<pair<int, int>>& r, int c, int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(checkPlace(r, c, i))
        {
            r.emplace_back(make_pair(c, i));
            if(c == n || findPlaces(r, c + 1, n))
                return true;
            r.pop_back();
        }
    }
    return false;
}

vector<string> getPlaces(int n)
{
    vector<pair<int, int>> r;
    findPlaces(r, 1, n);

    vector<string> res;
    for(int i = 1; i <= n; ++i)
    {
        string t;
        for(int j = 1; j <= n; ++j)
            t += '0';
        res.emplace_back(t);
    }
    for(auto& el : r)
        res[el.first - 1][el.second - 1] = '1';
    return res;
}

int main()
{
    int n;
    vector<string> res;

    ifstream fin;
    fin.open("input.txt");
    if(fin.is_open()) {
        fin >> n;
        fin.close();
    }

    res = getPlaces(n);

    fstream fout;
    fout.open("output.txt", ios::out);
    for(int i = 0; i < res.size(); i++)
        fout << res[i] << endl;
    fout.close();

    return 0;
}