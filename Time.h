// Time.h
//
// Time
// Version 1.4

#ifndef _Time_h_
#define _Time_h_

#include <iostream>

class Time
{
public:
    friend std::istream & operator>>(std::istream & in, Time & t);

    Time() : Time(99, 99) {}
    Time(int h) : Time(h, 0) {}
    Time(int h, int m) : hours_(h), minutes_(m) {}

    int hours() const { return hours_; }
    int minutes() const { return minutes_; }

    void set_hours(int new_hours) { hours_ = new_hours; }
    void set_minutes(int new_minutes) { minutes_ = new_minutes; }

    void set(int new_hours, int new_minutes = 0);

private:
    int hours_;
    int minutes_;
};

inline void Time::set(int new_hours, int new_minutes)
{
    hours_ = new_hours;
    minutes_ = new_minutes;
}

inline double operator-(const Time & t1, const Time & t2)
{
    return (t1.hours() + t1.minutes()/60.0) -
        (t2.hours() + t2.minutes()/60.0);
}

inline std::istream & operator>>(std::istream & in, Time & t)
{
    in >> t.hours_;
    in.get(); // colon
    in >> t.minutes_;
    return in;
}

inline std::ostream & operator<<(std::ostream & out, const Time & t)
{
    out << t.hours() << ':';
    if ( t.minutes() < 10 ) out << '0';
    out << t.minutes();
    return out;
}

#endif


