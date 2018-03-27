#include <string>
#include <fstream>

const std::string filesPath = "../../resources/files/";

void countSimb(const std::string& name, std::ofstream& res)
{
    std::size_t simb[256];
    for(int i = 0; i < 256; ++i)
        simb[i] = 0;

    std::ifstream file(filesPath + name, std::ifstream::in | std::ifstream::binary);
    char c;
    while(file.get(c))
        ++simb[static_cast<unsigned char>(c)];

    for(int i = 0; i < 255; ++i)
        res << simb[i] << ",";
    res << simb[255] << std::endl;
}

int main() {
    const std::string files[] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12",
                                  "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
                                  "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36" };

    std::ofstream res("../../resources/nsimb.csv");

    for(int i = 0; i < 36; ++i)
        countSimb(files[i], res);


    res.close();
    return 0;
}
