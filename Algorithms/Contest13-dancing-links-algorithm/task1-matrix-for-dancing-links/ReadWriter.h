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

    // read 1 int value and empty line
    int readInt()
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        int n;
        fin >> n;
        //empty line read
        std::string s;
        std::getline(fin, s);
        return n;
    }

    //read data in arr, arr should be initialized before this method
    void readData(char* up, char* down, char* left, char* right, int n)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");
        std::string s;
        //all 4 rows
        //N element in each
        fin.read(up, n);
        std::getline(fin, s); //read empty line

        fin.read(down, n);
        std::getline(fin, s); //read empty line

        fin.read(left, n);
        std::getline(fin, s); //read empty line

        fin.read(right, n);
        std::getline(fin, s); //read empty line
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