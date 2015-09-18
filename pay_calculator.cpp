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
const double kBonus = 5;

//The number of different periods in the day that are paid differently
const int kNumPaySectors = 3;

/*The size of the array is equal to the number of pay sectors, and should contain the
    amount an individual is paid per hour in that sector */
const double kPayRates[] = {kPayRate + kBonus, kPayRate, kPayRate + kBonus};

/*The size of the array is equal to kPaySectors + 1, this contains the boundaries of each sector*/
const int kPayBoundaries[] = {0, 6, 18, 24};

class Time
{
public:
    inline void initialize();
    inline void initialize(const int & hour, const int & minute);
    inline void read(istream & in);

    void print12(ostream & out) const;
    inline double minus(const Time & other) const;
    inline void print(ostream &out) const;

private:
    int hours_;
    int minutes_;
};

inline void Time::initialize()
{
    hours_ = minutes_ = 99;
}

inline void Time::initialize(const int & hour, const int & minute)
{
    hours_ = hour;
    minutes_ = minute;
}

inline void Time::read(istream & in)
{
    in >> hours_;
    in.get(); // colon
    in >> minutes_;
}

inline void Time::print(ostream & out) const
{
    out << hours_ << ':';
    if (minutes_ < 10) out << '0';
    out << minutes_;
}

void Time::print12(ostream & out) const
{
    if(hours_ % 12 == 0)
        out << 12;
    else if(hours_ > 12)
        out << hours_ -12;
    else
        out << hours_;

    out << ':';
    if(minutes_ < 10) out << '0';
    out << minutes_;

    if(hours_ < 12)
        out << " a.m.";
    else
        out << " p.m.";
}

inline double Time::minus(const Time & other) const
{
    return (hours_ + minutes_/60.0) -
        (other.hours_ + other.minutes_/60.0);
}

double amount_in_bounds(const double & range, const double & distance_from_lower, const double & distance_from_upper)
{
     double in_bounds{range};
     bool inside{false};
     if(distance_from_lower >= range || distance_from_upper >= range)
        return 0;

     if(distance_from_lower >= 0 && distance_from_lower < range)
         in_bounds -= distance_from_lower;

     if(distance_from_upper >= 0 && distance_from_upper < range)
         in_bounds -= distance_from_upper;

    return in_bounds;
}

double calculate_pay(const Time & in, const Time & out)
{
    Time t_low_bound;
    Time t_high_bound;

    double low_cut;
    double high_cut;

    double pay {0};

    t_high_bound.initialize(kPayBoundaries[0], 0);

    for(int pay_sector = 0; pay_sector < kNumPaySectors; pay_sector++)
    {
        t_low_bound = t_high_bound;

        t_high_bound.initialize(kPayBoundaries[pay_sector + 1], 0);

        double range { t_high_bound.minus(t_low_bound) };

        low_cut = in.minus(t_low_bound);
        high_cut = t_high_bound.minus(out);

        double in_range = amount_in_bounds(range, low_cut, high_cut);

        if(in_range > 0)
            pay += in_range * kPayRates[pay_sector];
    }

    return pay;
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
        start_time.read( ifs_input);
        Time stop_time;
        stop_time.read( ifs_input);

       // double pay = difference(stop_time, start_time) * kPayRate;
        double pay = calculate_pay(start_time, stop_time);

        ofs_output << employee_number << ' ';
        start_time.print( ofs_output);
        ofs_output << ' ';
        stop_time.print( ofs_output);
        ofs_output << " $" << fixed << setprecision(2) << pay
                   << endl;

        start_time.print12( cout);
        cout << ' ';
        stop_time.print12( cout);
        cout << ' ' << pay << endl;
    }

    return 0;
}








