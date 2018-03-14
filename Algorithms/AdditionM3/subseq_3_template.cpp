#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <set>

using namespace std;

void findSegments(const string& x, const string& y, int** arr, int i, int j, const string& s, set<string>& segments)
{
    if(arr[i][j] == 0) {
        segments.insert(s);
        return;
    }

    if(x[i - 1] == y[j - 1])
        findSegments(x, y, arr, i - 1, j - 1, x[i - 1] + s, segments);
    else
    {
        if(arr[i][j] == arr[i][j - 1])
            findSegments(x, y, arr, i, j - 1, s, segments);
        if(arr[i][j] == arr[i - 1][j])
            findSegments(x, y, arr, i - 1, j, s, segments);
    }
}

vector<string> getLCS(const string& x, const string& y)
{
    int lenX = x.length(), lenY = y.length();
    int** arr = new int*[lenX + 1];

    arr[0] = new int[lenY + 1];
    for(int i = 0; i <= lenY; ++i)
        arr[0][i] = 0;

    for(int i = 1; i <= lenX; ++i)
    {
        arr[i] = new int[lenY + 1];
        arr[i][0] = 0;
        for(int j = 1; j <= lenY; ++j)
        {
            if(x[i - 1] == y[j - 1])
                arr[i][j] = arr[i - 1][j - 1] + 1;
            else
                arr[i][j] = std::max(arr[i][j - 1], arr[i - 1][j]);
        }
    }


    set<string> segments;
    findSegments(x, y, arr, lenX, lenY, "", segments);

    for(int k = 0; k <= lenX; ++k)
        delete[] arr[k];
    delete[] arr;

    return vector<string>(segments.begin(), segments.end());
}

int main()
{
    string x;
    string y;
    vector<string> res;

    ifstream fin;
    fin.open("input.txt");
    if(fin.is_open()) {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    for(int i = 0; i < res.size(); i++)
        fout << res[i] << endl;
    fout.close();

    return 0;
}