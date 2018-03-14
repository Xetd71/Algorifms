#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "dna_repairer.h"

using namespace std;

static const char* INP_FILENAME = "../../resources/test5.in";

int main(int argc, char* argv[])
{
    try {
        DNARepairer dnarepairer;

        dnarepairer.readFile(INP_FILENAME);


        cout << "Broken DNAs" << endl;
        dnarepairer.printDNAStorage();

        dnarepairer.repairDNA();

        cout << "\nGood as it is" << endl;
        dnarepairer.printDNAStorage();
    } catch(exception& e) {
        cout << e.what();
    } catch(...) {
        cout << "Something wrong happend." << endl;
    }
    cout << endl;

    return EXIT_SUCCESS;
}