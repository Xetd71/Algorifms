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


//параметры:
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

struct Node
{
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    Node *head;

    int size;
    int id;
};

const int MAX_N = 8160;
Node* headHead = nullptr;
Node* solution[MAX_N];
int size = 0;

void cover(Node* col)
{
    col->left->right = col->right;
    col->right->left = col->left;
    for (Node* node = col->down; node != col; node = node->down)
    {
        for (Node* temp = node->right; temp != node; temp = temp->right)
        {
            temp->down->up = temp->up;
            temp->up->down = temp->down;
            temp->head->size--;
        }
    }
}

void uncover(Node* col)
{
    for (Node* node = col->up; node != col; node = node->up)
    {
        for (Node* temp = node->left; temp != node; temp = temp->left)
        {
            temp->head->size++;
            temp->down->up = temp;
            temp->up->down = temp;
        }
    }
    col->left->right = col;
    col->right->left = col;
}

void search(int k)
{
    if (headHead->right == headHead)
    {
        size = k;
        return;
    }

    Node* head = headHead->right;
    for (Node* temp = head->right; temp != headHead; temp = temp->right)
        if (temp->size < head->size)
            head = temp;

    cover(head);

    for (Node* temp = head->down; temp != head; temp = temp->down)
    {
        solution[k] = temp;
        for (Node* node = temp->right; node != temp; node = node->right)
        {
            cover(node->head);
        }

        search(k + 1);

        temp = solution[k];
        head = temp->head;
        for (Node* node = temp->left; node != temp; node = node->left) {
            uncover(node->head);
        }

        if(size != 0)
            return;
        solution[k] = nullptr;
    }

    uncover(head);
}

void buildLinkedList(char** matrix, int n, int m)
{
    headHead = new Node();
    headHead->left = headHead;
    headHead->right = headHead;
    Node* prevHead = headHead;

    for(int i = 0; i < m; ++i)
    {
        Node* head = new Node();
        head->size = 0;
        head->up = head;
        head->down = head;

        head->right = headHead;

        head->left = prevHead;
        prevHead->right = head;
        prevHead = head;
    }

    for(int i = 0; i < n; ++i)
    {
        Node* head = headHead->right;
        Node* prev = nullptr;
        for(int j = 0; j < m; ++j, head = head->right)
        {
            if(matrix[i][j] != '1')
                continue;
            Node* node = new Node();
            node->id = i;
            if(prev == nullptr) {
                prev = node;
                prev->right = node;
            }
            node->left = prev;
            node->right = prev->right;
            node->right->left = node;
            prev->right = node;
            node->head = head;
            node->down = head;
            node->up = head->up;
            head->up->down = node;
            head->up = node;
            ++head->size;
            if(head->down == head)
                head->down = node;
            prev = node;
        }
    }
}

void deleteLinkedList()
{
    for(Node* head = headHead->right; head != headHead; head = head->right)
    {
        Node* node = head->down;
        while(node != head)
        {
            Node* tmp = node;
            node = node->down;
            delete tmp;
        }
    }
    Node* head = headHead->right;
    while(head != headHead)
    {
        Node* tmp = head;
        head = head->right;
        delete tmp;
    }
}

//Основной метод решения задачи, параметры:
//n - размер исходной задачи и результата (NxN)
//up - доп. условия сверху, содержит буквы латинского алфавита и пробелы
//down - доп. условия снизу, содержит буквы латинского алфавита и пробелы
//left - доп. условия слева, содержит буквы латинского алфавита и пробелы
//up - доп. условия справа, содержит буквы латинского алфавита и пробелы
//result - матрица решения NxN, представлено как массив строчек, содержащих символы 'А-Z' и '+', для обозначения отсутствия буквы
void solve(char* up, char* down, char* left, char* right, char** result, int n)
{
    char** matrix;
    int rows, cols;
    createMatrix(up, down, left, right, n, matrix, rows, cols);
    buildLinkedList(matrix, rows, cols);
    search(0);

    for(int i = 0; i < size; ++i) {
        int id = solution[i]->id;
        result[id / (n * n)][(id % (n * n)) / n] = (id % n == n - 1 ? '+' : (char)('A' + id % n));
    }
    deleteLinkedList();
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

    //Создаем массив, но не заполняем нулями, так как в методе все равно будет заполнена каждая ячейка
    char** result = new char*[n];
    for (int i=0; i< n; i++)
        result[i] = new char[n];
    //Основной алгоритм, возвращает результат как матрицу решения, память уже выделена под result
    solve(up, down, left, right, result, n);

    //выводим результат в файл
    rw.writeInt(n);
    rw.writeResult(result, n);

    //освобождаем память
    delete[] up;
    delete[] down;
    delete[] left;
    delete[] right;

    for (int i = 0; i < n; i++)
        delete[] result[i];
    delete[] result;

    return 0;
}