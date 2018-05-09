#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
#include <algorithm>
#include <queue>

using namespace std;

struct lessF
{
    bool operator()(const pair<int, int>& v1, const pair<int, int>& v2)
    {
        return v1.second > v2.second;
    }
};

void getAStar(int n, int start, int goal, vector<vector<int>>& matrix, vector<int>& heuris, vector<int>& path)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, lessF> opened;
    opened.push({start, 0});

    unordered_map<int, int> cameFrom;
    cameFrom[start] = -1;
    unordered_map<int, int> gs;
    gs[start] = 0;

    while(!opened.empty())
    {
        int x = opened.top().first;
        opened.pop();

        if(x == goal) {
            for(int i = goal; i != -1; i = cameFrom[i])
                path.insert(path.begin(), i);
            return;
        }

        for(int i = 0; i < n; ++i) {
            if(x == i || matrix[x][i] == -1)
                continue;

            int g = gs[x] + matrix[x][i];
            if(gs.count(i) == 0 || gs[i] > g) {
                gs[i] = g;
                opened.push({i, g + heuris[i]});
                cameFrom[i] = x;
            }
        }
    }
}

int main()
{
    int n;
    int start;
    int goal;
    vector<vector<int>> matrix;
    vector<int> heuris;
    vector<int> path = vector<int>();

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> n;
        fin >> start;
        fin >> goal;
        matrix = vector<vector<int>>(n);
        heuris = vector<int>(n);
        for (int i = 0; i < n; i++)
        {
            matrix[i] = vector<int>(n);
            for (int j = 0; j < n; j++)
                fin >> matrix[i][j];
        }
        for (int i = 0; i < n; i++)
            fin >> heuris[i];

        fin.close();
    }

    getAStar(n, start, goal, matrix, heuris, path);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < path.size(); i++)
        fout << path[i] << " ";
    fout.close();

    return 0;
}