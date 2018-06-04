#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void createList(vector<string>& names, vector<vector<bool>>& relations, int k, vector<string>& res, bool* unvisited)
{
    res.emplace_back(names[k]);
    vector<int> name;
    for(int i = 0; i < relations.size(); ++i)
    {
        if(relations[k][i])
            name.emplace_back(i);
    }
    sort(name.begin(), name.end(), [&names](int l, int r) { return names[l] < names[r]; });
    for(int& n : name)
    {
        if(unvisited[n])
        {
            unvisited[n] = false;
            createList(names, relations, n, res, unvisited);
        }
    }
}

vector<string> getList(vector<string>& names, vector<vector<bool>>& relations, int k)
{
    vector<string> res;
    int n = relations.size();
    bool unvisited[n];
    for(int i = 0; i < n; ++i)
        unvisited[i] = true;

    unvisited[k] = false;
    createList(names, relations, k, res, unvisited);
    return res;
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    int startIndex;

    ifstream fin;
    fin.open("input.txt");
    if(fin.is_open()) {
        string str = "";
        getline(fin, str);

        while(str != "#") {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        relations = vector<vector<bool>>(names.size());

        for(int i = 0; i < names.size(); i++) {
            relations[i] = vector<bool>(names.size());
            for(int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }

        getline(fin, str);

        while(str != "#") {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            relations[b][a] = true;
            getline(fin, str);
        }

        fin >> startIndex;

        fin.close();
    }

    vector<string> res = getList(names, relations, startIndex - 1);

    fstream fout;
    fout.open("output.txt", ios::out);
    for(int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}