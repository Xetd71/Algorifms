#include "ReadWriter.h"

using namespace std;
const Edge NULL_EDGE{ -1, -1, 30001, -1 };
//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    int n = N;
    vector<int> component;
    vector<bool> used(M, false);
    vector<Edge> chipedges(n);
    for (int i = 0; i < N; ++i)
        component.emplace_back(i);
    while (n > 1)
    {
        fill(chipedges.begin(), chipedges.begin() + n, NULL_EDGE);
        for (int i = 0; i < M; ++i)
        {
            if (!used[i] && component[edges[i].A] != component[edges[i].B])
            {
                if (edges[i].W < chipedges[component[edges[i].A]].W)
                    chipedges[component[edges[i].A]] = edges[i];
                if (edges[i].W < chipedges[component[edges[i].B]].W)
                    chipedges[component[edges[i].B]] = edges[i];
            }
        }
        int s = 0;
        for (int i = 0; i < N; ++i)
        {
            Edge e = chipedges[i];
            if (!used[e.number] && e.W != NULL_EDGE.W)
            {
                ++s;
                int ca = component[e.A], cb = component[e.B];
                used[e.number] = true;
                result.emplace_back(e);
                for (int k = 0; k < N; ++k) {
                    if (component[k] == ca)
                        component[k] = cb;
                    if (component[k] > ca)
                        --component[k];
                }
            }
        }
        n -= s;
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