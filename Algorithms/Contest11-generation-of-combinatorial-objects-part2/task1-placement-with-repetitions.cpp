#include <fstream>
#include <vector>
using namespace std;

string printCombination(long n, long m, long k)
{
    string out;
    long i = m - 1;

    if(k == 1L)
    {
        for(; i > 0; --i)
            out += "1 ";
        out += '1';
        return out;
    }

    vector<long> res;
    for(k -= 1L; k > 0 && i >= 0; --i, k /= n)
        res.emplace_back(k % n + 1L);
    for(; i >= 0; --i)
        out += "1 ";
    for(i = res.size() - 1; i > 0; --i)
        out += to_string(res[i]) + ' ';
    out += to_string(res[0]);
    return out;
}

int main()
{
    ios::sync_with_stdio(false);
    ifstream input("input.txt");
    ofstream output("output.txt");
    long n, m, k;
    input >> n >> m >> k;
    output << printCombination(n, m, k);
    input.close();
    output.close();
    return 0;
}
