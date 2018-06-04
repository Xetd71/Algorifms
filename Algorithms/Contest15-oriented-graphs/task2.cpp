#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void dfs1(int v, vector<int>& order, vector<bool>& used, vector<vector<bool>>& graph)
{
    used[v] = true;
    for(int i = 0; i < graph.size(); ++i)
        if (graph[v][i] && !used[i])
            dfs1(i, order, used, graph);
    order.emplace_back(v);
}

void dfs2(int v, vector<string>& component, vector<bool>& used, vector<string>& names, vector<vector<bool>>& graph)
{
    used[v] = true;
    component.emplace_back(names[v]);
    for(int i = 0; i < graph.size(); ++i)
        if(graph[i][v] && !used[i])
            dfs2(i, component, used, names, graph);
}

vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& graph)
{
    vector<vector<string>> res;
    vector<bool> used(graph.size(), false);
    vector<int> order;
    for(int i = 0; i < graph.size(); ++i)
        if(!used[i])
            dfs1(i, order, used, graph);

    used.assign(graph.size(), false);
    for(int i = graph.size() - 1; i >= 0; --i)
    {
        int v = order[i];
        if(!used[v])
        {
            vector<string> component;
            dfs2(v, component, used, names, graph);
            sort(component.begin(), component.end());
            res.emplace_back(component);
        }
    }

    sort(res.begin(), res.end(), [](vector<string>& l, vector<string>& r) { return l.front() < r.front(); });
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

        relations = vector < vector < bool >> (names.size());

        for(int i = 0; i < names.size(); i++) {
            relations[i] = vector<bool>(names.size());
            for(int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }

        getline(fin, str);

        while(fin) {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }

        fin.close();
    }

    vector <vector<string>> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for(int i = 0; i < res.size(); i++) {
        for(int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }
    fout.close();

    return 0;
}