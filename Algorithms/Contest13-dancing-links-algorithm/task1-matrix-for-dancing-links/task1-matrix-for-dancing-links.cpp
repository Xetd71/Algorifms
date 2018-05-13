#include "ReadWriter.h"
#include <vector>
using namespace std;

vector<pair<int, int>> getRowsRestrictions(int n)
{
    vector<pair<int, int>> restrictions;
    int p = 0, ofs = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                restrictions.emplace_back(make_pair(i * n * n + j * n + k, p));
                p = (p + 1) % n + ofs;
            }
        }
        ofs += n;
        p = ofs;
    }
    return restrictions;
}

vector<pair<int, int>> getColumnsRestrictions(int n)
{
    int p = 0, k = n * n;
    vector<pair<int, int>> restrictions;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < k; ++j) {
            restrictions.emplace_back(make_pair(i * n * n + j, p));
            p = (p + 1) % k;
        }
    }
    return restrictions;
}

vector<pair<int, int>> getOneLetterRestrictions(int n)
{
    int p = 0, k = n * n;
    vector<pair<int, int>> restrictions;

    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < n; ++j)
            restrictions.emplace_back(make_pair(i * n + j, p));
        p = (p + 1) % k;
    }
    return restrictions;
}

int getNumb(char c, int n) {
    if(c == ' ')
        return n - 1;
    return c - 'A';
}

int getRow(int i, int j, char c, int n) {
    return (i * n + j) * n + getNumb(c, n);
}

vector<pair<int, int>> getLetterRestrictions(char* up, char* down, char* left, char* right, int n)
{
    vector<pair<int, int>> restrictions;
    for(int i = 0; i < n; ++i) {
        if(up[i] != ' ') {
            int t = getRow(0, i, up[i], n);
            restrictions.emplace_back(make_pair(t, getRow(0, i, ' ', n)));
            restrictions.emplace_back(make_pair(t, t + n * n));
        }
        if(down[i] != ' ') {
            int t = getRow(n - 1, i, down[i], n);
            restrictions.emplace_back(make_pair(t, getRow(n - 1, i, ' ', n)));
            restrictions.emplace_back(make_pair(t, t - n * n));
        }
        if(right[i] != ' ') {
            int t = getRow(i, n - 1, right[i], n);
            restrictions.emplace_back(make_pair(t, getRow(i, n - 1, ' ', n)));
            restrictions.emplace_back(make_pair(t, t - n));
        }
        if(left[i] != ' ') {
            int t = getRow(i, 0, left[i], n);
            restrictions.emplace_back(make_pair(t, getRow(i, 0, ' ', n)));
            restrictions.emplace_back(make_pair(t, t + n));
        }
    }

    return restrictions;
}


//Основной метод решения задачи, параметры:
//n - размер векторов условия
//up - доп. условия сверху, содержит буквы латинского алфавита и пробелы
//down - доп. условия снизу, содержит буквы латинского алфавита и пробелы
//left - доп. условия слева, содержит буквы латинского алфавита и пробелы
//up - доп. условия справа, содержит буквы латинского алфавита и пробелы
///Выходные параметры:
//result - матрица ограничений для задачи, содержит символы '0' и '1', других не содержит.
//передается по ссылке, чтобы потом можно было прочитать значение из main
//rows - количество строк в матрице результата
//cols - количество столбцов в матрице результата
void createMatrix(char* up, char* down, char* left, char* right, int n, char**& result, int& rows, int& cols)
{
    vector<pair<int, int>> rr = getRowsRestrictions(n);
    vector<pair<int, int>> rc = getColumnsRestrictions(n);
    vector<pair<int, int>> olr = getOneLetterRestrictions(n);
    vector<pair<int, int>> lr = getLetterRestrictions(up, down, left, right, n);
    cols = 3 * n * n + lr.size();
    rows = n * n * n;

    result = new char*[rows];
    for(int i = 0; i < rows; ++i) {
        result[i] = new char[cols];
        for(int j = 0; j < cols; ++j)
            result[i][j] = '0';
    }

    for(pair<int, int>& p : rr)
        result[p.first][p.second] = '1';
    int ofs = n * n;
    for(pair<int, int>& p : rc)
        result[p.first][p.second + ofs] = '1';
    ofs = 2 * n * n;
    for(pair<int, int>& p : olr)
        result[p.first][p.second + ofs] = '1';
    ofs = 3 * n * n;
    for(pair<int, int>& p : lr) {
        result[p.first][ofs] = '1';
        result[p.second][ofs] = '1';
        ++ofs;
    }
}


int main()
{
    ReadWriter rw;
    //читаем параметры
    int n = rw.readInt();

    char* up = new char[n];
    char* down = new char[n];
    char* left = new char[n];
    char* right = new char[n];

    rw.readData(up, down, left, right, n);

    //Память здесь не выделяется, так как размер неизвестен
    char** result = nullptr;
    //Основной алгоритм, возвращает результат как матрицу 
    int rows = 0, cols = 0;
    createMatrix(up, down, left, right, n, result, rows, cols);

    //выводим результат в файл
    rw.writeInts(rows, cols);
    rw.writeMatrix(result, rows, cols);
    
    //освобождаем память
    delete[] up;
    delete[] down;
    delete[] left;
    delete[] right;

    for (int i = 0; i < rows; i++)
        delete[] result[i];
    delete[] result;

    return 0;
}