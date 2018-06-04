#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <algorithm>

using namespace std;

vector<string> getList(vector<string> names, vector<vector<bool>> relations, int k)
{
    vector<string> res;
    int n = relations.size();
    bool unvisited[n];
    for(int i = 0; i < n; ++i)
        unvisited[i] = true;

    vector<int> relatives;
    unvisited[k] = false;
    relatives.emplace_back(k);
    while(!relatives.empty())
    {

        vector<int> tmp;
        vector<string> name;
        for(int& r : relatives)
        {
            name.emplace_back(names[r]);
            for(int i = 0; i < n; ++i)
            {
                if(relations[r][i] && unvisited[i])
                {
                    tmp.emplace_back(i);
                    unvisited[i] = false;
                }
            }

        }
        sort(name.begin(), name.end());
        res.insert(res.end(), name.begin(), name.end());
        relatives = tmp;
    }
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