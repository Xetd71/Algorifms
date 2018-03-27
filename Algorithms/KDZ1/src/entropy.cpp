#include <fstream>
#include <map>
#include <cmath>

double countEntropy(const std::string& pathFile)
{
    std::ifstream file(pathFile, std::ifstream::in | std::ifstream::binary);
    if(!file.good())
        throw std::invalid_argument("Can't open file: " + pathFile);
    std::map<char, std::size_t> count;
    char c;
    long long n = 0;
    while(file.get(c))
    {
        if(count.count(c) > 0)
            count[c] += 1;
        else
            count[c] = 1;
        ++n;
    }
    file.close();

    double total = 0;
    for(auto& c : count) {
        double p = (double)c.second / n;
        total -= p * std::log2(p);
    }
    return total;
}

int main()
{
    const std::string filesPath = "../../resources/files/";
    const std::string files[] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12",
                                  "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
                                  "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36" };

    std::ofstream entropy("../../resources/entropy.csv");
    for(int i = 0; i < 36; ++i) {
        entropy << countEntropy(filesPath + files[i]) << "\n";
    }

    entropy.close();
    return 0;
}