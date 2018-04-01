#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

//Задача реализовать этот метод
//param N - количество камней
//param M - ограничения на вес
//param stones - массив размера N, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int N, int W, int* stones, vector<int>& res)
{
    int s[N + 1][W + 1];

    for(int i = 0; i <= W; ++i)
        s[0][i] = 0;

    for(int i = 1; i <= N; ++i)
    {
        s[i][0] = 0;
        for(int j = 1; j <= W; ++j)
        {
            int val = j - stones[i - 1];
            s[i][j] = val >= 0
                      ? max(s[i - 1][val] + stones[i - 1], s[i - 1][j])
                      : s[i - 1][j];
        }
    }

    for(int i = N, j = W; s[i][j] > 0; --i)
    {
        if(s[i][j] != s[i - 1][j])
        {
            res.emplace_back(stones[i - 1]);
            j -= stones[i - 1];
        }
    }
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int* arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int i = 0; i < res.size(); i++)
        sum += res.at(i);

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}