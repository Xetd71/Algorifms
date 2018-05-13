#include <iostream>
#include <fstream>
#include <string>

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

    // read 2 int value and empty line
    void readInts(int& n, int& m)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        fin >> n;
        fin >> m;
        //empty line read
        std::string s;
        std::getline(fin, s);
    }

    //read matrix NxM, N rows with M elements in each
    void readMatrix(char** matrix, int n, int m)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");
        std::string s;

        for (int i = 0; i < n; i++)
        {
            fin.read(matrix[i], m);
            std::getline(fin, s); //read empty line
        }
    }


    //write result NxM matrix, N rows with M elements in each
    void writeMatrix(char** result, int n, int m)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        //by rows
        for (int i = 0; i < n; i++)
        {
            fout.write(result[i], m);
            fout << std::endl;
        }
    }

    //Размер матрицы
    void writeInts(int n, int m)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout << n << ' ' << m << std::endl;
    }
};