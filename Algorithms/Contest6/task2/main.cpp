#include "ReadWriter.h"
//Node.h подключен в ReadWriter.h, поэтому здесь не надо

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

//Задание реализовать метод декодирования
void decodeLZ77(Node* arr, int n, string& res)
{
    res = "";
    for(int i = 0; i < n; ++i)
    {
        for(int k = 0; k < arr[i].len ; ++k)
            res += res[res.length() - arr[i].offs];
        res += arr[i].ch;
    }
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    
    int n = rw.readInt();
    Node* arr = new Node[n];

    rw.readCode(arr, n);

    string res = "";
    //декодируем в строку
    decodeLZ77(arr, n, res);
    //записываем ответ в файл
    rw.writeString(res);

    delete[] arr;

    return 0;
}