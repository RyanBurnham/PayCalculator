
// main.cpp

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <iomanip>
using std::fixed;
using std::setprecision;
#include <iostream>
using std::cout;
using std::cin;
using std::istream;
using std::ostream;
#include <string>
using std::string;

#include "Time.h"

const double kPayRate = 12;

int main()
{
    cout << "Name of input file: ";
    string input_file_name;
    getline(cin, input_file_name);

    ifstream ifs_input(input_file_name);
    if (!ifs_input) {
        cout << "Could not open file.\n";
        return 1;
    }

    cout << "Name of output file: ";
    string output_file_name;
    getline(cin, output_file_name);

    ofstream ofs_output(output_file_name);
    if (!ofs_output) {
        cout << "Could not open output file.\n";
        return 1;
    }

    int employee_number = -1;
    Time start_time, stop_time;

    while (ifs_input >> employee_number) {
        ifs_input >> start_time >> stop_time;

        double pay = (stop_time - start_time) * kPayRate;

        ofs_output << employee_number << ' '
                   << start_time << ' ' << stop_time << " $"
                   << fixed << setprecision(2) << pay << '\n';
    }

    return 0;
}

