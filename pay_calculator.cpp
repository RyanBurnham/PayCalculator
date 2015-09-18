// Pay calculator
// Version 1

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;

#include <iomanip>
using std::fixed;
using std::setprecision;

// using namespace std;

const double kPayRate = 12;

struct Time
{
    int hours;
    int minutes;
};

void initialize(Time & t)
{
    t.hours = t.minutes = 99;
}

void read(Time & t, istream & in)
{
    in >> t.hours;
    in.get(); // colon
    in >> t.minutes;
}

void print(const Time & t, ostream & out)
{
    out << t.hours << ':';
    if (t.minutes < 10) out << '0';
    out << t.minutes;
}

double difference(const Time & t1, const Time & t2)
{
    return (t1.hours + t1.minutes/60.0) -
        (t2.hours + t2.minutes/60.0);
}

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

    int employee_number;
    while (ifs_input >> employee_number) {
        Time start_time;
        read(start_time, ifs_input);
        Time stop_time;
        read(stop_time, ifs_input);

      //  double pay = difference(stop_time, start_time) * kPayRate;
        double pay = calculate_pay(start_time, stop_time);

        ofs_output << employee_number << ' ';
        print(start_time, ofs_output);
        ofs_output << ' ';
        print(stop_time, ofs_output);
        ofs_output << " $" << fixed << setprecision(2) << pay
                   << endl;
    }

    return 0;
}








