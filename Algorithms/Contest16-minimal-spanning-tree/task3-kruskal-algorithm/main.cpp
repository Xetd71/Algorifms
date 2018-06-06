#include "ReadWriter.h"
#include <stdlib.h>

using namespace std;

int dsuGet (int v, vector<int>& p)
{
    return (v == p[v]) ? v : (p[v] = dsuGet(p[v], p));
}

void dsuUnite(int a, int b, vector<int>& p)
{
    a = dsuGet(a, p);
    b = dsuGet(b, p);
    if (a != b)
    {
        if (rand() & 1)
            swap(a, b);
        p[a] = b;
    }
}

//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    sort(
        edges.begin(),
        edges.end(),
        [](const Edge& l, const Edge& r) { return l.W < r.W; }
    );
    vector<int> p(N);
    for(int i = 0; i < N; ++i)
        p[i] = i;
    int cost = 0;
    for(int i = 0; i < M; ++i)
    {
        int a = edges[i].A, b = edges[i].B, w = edges[i].W;
        if(dsuGet(a, p) != dsuGet(b, p))
        {
            cost += w;
            result.emplace_back(edges[i]);
            dsuUnite(a, b, p);
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