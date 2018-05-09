#include <fstream>
#include <vector>
using namespace std;

string getPlacement(long n, long k)
{
    string out;
    long m = n;

    if(k == 1L)
    {
        for(; m > 1; --m)
            out += "1 ";
        out += '1';
        return out;
    }

    vector<long> res;
    for(k -= 1L; k > 0 && m >= 1; k /= m--)
        res.emplace_back(k % m + 1L);
    for(; m >= 1; --m)
        out += "1 ";
    for(m = res.size() - 1; m > 0; --m)
        out += to_string(res[m]) + ' ';
    out += to_string(res[0]);
    return out;
}

int main()
{
    ios::sync_with_stdio(false);
    ifstream input("input.txt");
    ofstream output("output.txt");
    long n, k;
    input >> n >> k;
    output << getPlacement(n, k);
    input.close();
    output.close();
    return 0;
}