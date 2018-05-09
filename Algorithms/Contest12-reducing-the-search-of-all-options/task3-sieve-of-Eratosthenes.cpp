#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> getEratosthenes(int n)
{
    vector<int> res;
    res.emplace_back(1);
    vector<bool> privates(n + 1, true);
    for(int i = 0; i <= n; ++i)
        privates[i] = true;
    for(int i = 2; i <= n; ++i)
    {
        if(privates[i])
        {
            res.emplace_back(i);
            for(long long j = (long long)i * i; j <= n; j += i)
                privates[j] = false;
        }
    }
    return res;
}

int main()
{
    int n;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> n;
        fin.close();
    }

    res = getEratosthenes(n);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << " ";
    fout.close();

    return 0;
}