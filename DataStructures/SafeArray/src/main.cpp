#include <iostream>

#include <fstream>
#include "safearray.h"
#include "subject.h"


using namespace std;


int main()
{
    //using namespace xi;

    //cout << "Hello, World!" << endl;

    //// Simple safearray
    //SafeArray<int> sa;

    //system("pause");

    //return 0;

    using namespace xi;

    try {
        size_t length = 10;
        SafeArray<int> intArray(length);
        for(size_t i = 0; i < intArray.getCapacity(); i++)
            intArray[i] = i;
        std::cout << intArray;
    } catch(exception e) {
        cout << e.what();
    }


    /*ifstream inf("d:\\Visual Studio 2017\\Projects\\SaveArray\\res\\raw\\subjects.txt");
    xi::SafeArray<xi::Subject> subjs = xi::SafeArray<xi::Subject>(10);
    for(int i = 0; i < 10; i++) {
        inf >> subjs[i];
    }
    for(int i = 0; i < 10; i++) {
        cout << subjs[i];
    }*/
    system("pause");
}