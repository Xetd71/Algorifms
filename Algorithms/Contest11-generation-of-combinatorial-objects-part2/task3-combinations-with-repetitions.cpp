#include <fstream>
using namespace std;

string getCombination(int n, int m, int k)
{
    string out;
    int c[m];
    c[0] = n;
    for(int i = 1; i < m; ++i)
        c[i] = 0;

    int p = m - 1;
    for(int i = 1; i < k; ++i)
    {
        int j = p - 1;
        while(c[j] == 0) --j;
        --c[j];
        ++c[j + 1];
        if(c[p] != 0 && j + 1 != p)
        {
            c[j + 1] += c[p];
            c[p] = 0;
        }
    }

    for(int i = 0; i < p; ++i)
        out += to_string(c[i]) + ' ';
    out += to_string(c[p]);
    return out;
}

int main()
{
    ios::sync_with_stdio(false);
    ifstream input("input.txt");
    ofstream output("output.txt");
    int n, m, k;
    input >> n >> m >> k;
    output << getCombination(n, m, k);
    input.close();
    output.close();
    return 0;
}