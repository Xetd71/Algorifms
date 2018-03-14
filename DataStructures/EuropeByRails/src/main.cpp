//#pragma warning (disable:4786)
//#pragma warning (disable:4503)

#include <iostream>
#include <fstream>
#include <string>

#include "city.h"
#include "service.h"
#include "rail_system.h"

using namespace std;

// For test
bool check(const Route& expected, RailSystem& rs)
{
    Route actual = rs.getCheapestRoute(expected.from, expected.to);
    return actual == expected;
}

int main(int argc, char* argv[])
{
    try {
        RailSystem rs("../../services.txt");

        while(true) {
            cout << "\n\nEnter a start and destination city:  ('quit' to exit)\n";

            string from, to;
            cin >> from;
            if(from == "quit")
                break;
            cin >> to;

            if(rs.is_valid_city(from) && rs.is_valid_city(to))
                rs.output_cheapest_route(from, to, cout);
            else
                cout << "Please enter valid cities\n\n";
        } // while

        return 0;   // EXIT_SUCCESS; // именованная константа здесь смотрится, конечно, лучше но не во всех компиляторах она берется "из коробки"
    } catch(exception& e) {
        cerr << e.what() << endl;
    } catch(...) {
        cerr << "Unknown exception caught\n";
    }

    return 1; // EXIT_FAILURE; // см. замечание выше
}
