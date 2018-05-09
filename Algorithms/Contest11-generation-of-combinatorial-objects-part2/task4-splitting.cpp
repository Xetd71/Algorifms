#include <fstream>
using namespace std;

void printArray(int* arr, int k, ofstream& out)
{
    for(int i = 0; i < k; ++i)
        out << arr[i] << ' ';
    out << arr[k] << '\n';
}

void printSplittings(int n, ofstream& out)
{
    int arr[n];
    for(int i = 0; i < n; ++i)
        arr[i] = 1;
    int last = n - 1;
    while(last != 0)
    {
        printArray(arr, last, out);
        int k = last - 1, sum = arr[last];
        while(k != 0 && arr[k - 1] == arr[k])
        {
            sum += arr[k];
            --k;
        }
        ++arr[k];
        if(sum != last - k)
            for(int i = 1; i < sum; ++i)
                arr[k + i] = 1;
        last = k + sum - 1;
    }
    out << n << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    ifstream input("input.txt");
    ofstream output("output.txt");
    int n, m, k;
    input >> n >> m >> k;
    printSplittings(n, output);
    input.close();
    output.close();
    return 0;
}