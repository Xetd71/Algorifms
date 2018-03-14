#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Node.h"

class ReadWriter
{
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    ReadWriter()
    {
        fin.open("input.txt", std::ios::in);
        fout.open("output.txt", std::ios::out);
    }

    //read 1 line
    void readString(std::string& s)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        std::getline(fin, s);
    }

    // read 1 int value
    int readInt()
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        int n;
        fin >> n;
        return n;
    }

    //read data in arr, arr should be initialized before this method
    void readCode(Node* arr, int n)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        int offs, len;
        char ch;
        for (int i = 0; i < n; i++)
        {
            fin >> offs;
            fin >> len;
            fin >> ch;
            arr[i] = Node(offs, len, ch);
        }
    }

    //Another task: write decoded text
    void writeString(std::string& s)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout << s;
    }
};