#include "ReadWriter.h"
#include <set>

using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    vector<vector<int>> g(N);
    for(int i = 0; i < M; ++i) {
        g[edges[i].A].emplace_back(i);
        g[edges[i].B].emplace_back(i);
    }

    vector<int> min(N, -1);
    min[0] = -2;
    set<pair<int, int>> q;
    q.insert(make_pair(0, 0));
    for(int i = 0; i < N; ++i)
    {
        if(q.empty())
            return;

        int v = q.begin()->second;
        q.erase(q.begin());
        if(min[v] >= 0) {
            result.emplace_back(edges[min[v]]);
            min[v] = -2;
        }

        for(int j : g[v])
        {
            Edge e = edges[j];
            int to = v == e.A ? e.B : e.A;
            if(min[to] == -1 || (min[to] >= 0 && e.W < edges[min[to]].W))
            {
                q.erase(make_pair(edges[min[to]].W, to));
                min[to] = e.number;
                q.insert(make_pair(e.W, to));
            }
        }
    }
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}