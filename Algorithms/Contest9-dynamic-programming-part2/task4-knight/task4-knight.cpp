#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"

using namespace std;


//Можно добавлять любые вспомогательные методы и классы для решения задачи.
long long** board;
int N_MAX, M_MAX;

long long getWays(int i, int j)
{
    if(i < 0 || j < 0 || i >= N_MAX || j >= M_MAX)
        return 0;

    if(board[i][j] != -1)
        return board[i][j];

    if(i == 0)
        return board[i][j] = j >= 2 ? getWays(i + 1, j - 2) : 0;
    if(i == 1)
        return board[i][j] = j >= 2 ? getWays(i + 1, j - 2) + getWays(i - 1, j - 2) : 0;
    if(j == 0)
        return board[i][j] = i >= 2 ? getWays(i - 2, j + 1) : 0;
    if(j == 1)
        return board[i][j] = i >= 2 ? getWays(i - 2, j - 1) + getWays(i - 2, j + 1) : 0;

    return board[i][j] = getWays(i + 1, j - 2) + getWays(i - 1, j - 2)
                       + getWays(i - 2, j - 1) + getWays(i - 2, j + 1);
}

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    board = new long long*[N];

    N_MAX = N, M_MAX = M;
    for(int i = 0; i < N; ++i)
    {
        board[i] = new long long[M];
        for(int j = 0; j < M; ++j)
            board[i][j] = -1;
    }
    board[0][0] = 1;
    long long res = getWays(N - 1, M - 1);
    for(int i = 0; i < N; ++i)
        delete[] board[i];
    delete[] board;
    return res;
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}