#include "Solver.h"
#include <algorithm>    //swap
using namespace std;

//You can add some methods in main.cpp file

int main()
{
    ReadWriter rw;

    Student* students = nullptr;
    Ski* skis = nullptr;
    int n;

    //Read n from file
    n = rw.readInt();

    //Create arrays
    students = new Student[n];
    skis = new Ski[n];

    //read Students and Skis from file
    rw.readStudents(students, n);
    rw.readSkis(skis, n);

    //Find pairs
    Solver s;
    s.findPairs(students, skis, n);

    //Write answer to file
    rw.writeStudentsAndSkis(students, skis, n);

    delete[] students;
    delete[] skis;
    return 0;
}

void qSort(Student* students, Ski* skis, int left, int right)
{
    //Sort students
    int i1 = left, j1 = right, p1;
    Ski skx = skis[(left + right) / 2];
    do {
        for (; compare(students[i1], skx) > 0; ++i1);
        for (; compare(students[j1], skx) < 0; --j1);
        if (i1 <= j1) {
            swap(students[i1], students[j1]);
            if (compare(students[i1], skx) == 0)
                p1 = i1;
            if (compare(students[j1], skx) == 0)
                p1 = j1;
            ++i1;
            --j1;
        }
    } while (i1 <= j1);

    //Sort skis
    Student stx = students[p1];
    int i2 = left, j2 = right, p2;
    do {
        for (; compare(stx, skis[i2]) < 0; ++i2);
        for (; compare(stx, skis[j2]) > 0; --j2);
        if (i2 <= j2) {
            swap(skis[i2], skis[j2]);
            if(compare(stx, skis[i2]) == 0)
                p2 = i2;
            if(compare(stx, skis[j2]) == 0)
                p2 = j2;
            ++i2;
            --j2;
        }
    } while (i2 <= j2);

    if(j1 < j2)
        swap(skis[j2], skis[p2]);
    if(j1 > j2)
        swap(students[j1--], students[p1]);
    if(i1 > i2)
        swap(skis[i2], skis[p2]);
    if(i1 < i2)
        swap(students[i1++], students[p1]);

    //Recursive sort
    if (left < j1)
        qSort(students, skis, left, j1);
    if (i1 < right)
        qSort(students, skis, i1, right);

}


void qSortId(Student* students, Ski* skis, int left, int right)
{
    //Sort students and skis by id
    int i = left;
    int j = right;
    int x = students[(left + right) / 2].id;
    do {
        for (; students[i].id < x; ++i);
        for (; students[j].id > x; --j);
        if (i <= j) {
            swap(students[i], students[j]);
            swap(skis[i++], skis[j--]);
        }
    } while (i <= j);

    if (left < j)
        qSortId(students, skis, left, j);
    if (i < right)
        qSortId(students, skis, i, right);
}

//You can add some methods in main.cpp file
//Задача реализовать этот метод, можно добавлять любые вспомогательные методы в этот файл.
void Solver::findPairs(Student* students, Ski* skis, int n)
{
    qSort(students, skis, 0, n - 1);
    qSortId(students, skis, 0, n - 1);
}
