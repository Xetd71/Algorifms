#include "ReadWriter.h"

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

const int MAX_N = 150;
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
//matrix - матрица NxM, представленная как N массивов по строкам, в каждом по M элементов '0' или '1'
//n, m - размеры матрицы
//result - массив для вывода решения, содержит строки из матрицы,
//для него надо выделить память здесь, передается по ссылке, чтобы можно было изменить указатель и получить это значение из main
//resultSize - количество строк в результате, передается по ссылке, чтобы можно было получить значение из main
void solve(char** matrix, int n, int m, char**& result, int& resultSize)
{
    buildLinkedList(matrix, n, m);
    search(0);
    resultSize = size;
    result = new char*[size];
    for(int i = 0; i < size; ++i)
    {
        result[i] = new char[m];
        for(int j = 0; j < m; ++j)
            result[i][j] = matrix[solution[i]->id][j];
    }
    deleteLinkedList();
}


int main()
{
    ReadWriter rw;
    //читаем параметры
    int n, m;
    rw.readInts(n, m);

    char** matrix = new char*[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new char[m];
    //читаем матрицу
    rw.readMatrix(matrix, n, m);

    //Память под result не выделяется здесь, так как неизвестно какое количество строк войдет в решение
    //Предлагается выделить память прямо в методе solve
    int resultSize = 0; //количество строк в решении
    char** result = nullptr;
    solve(matrix, n, m, result, resultSize);

    //выводим результат в файл
    rw.writeInts(resultSize, m);
    rw.writeMatrix(result, resultSize, m);

    //освобождаем память матрицы, которую выделяли здесь
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    //освобождаем память массива результата, которая здесь не выделялась...
    for (int i = 0; i < resultSize; i++)
        delete[] result[i];
    delete[] result;

    return 0;
}