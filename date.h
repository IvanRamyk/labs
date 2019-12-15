#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>



struct Date
{
    Date() = default;
    Date(int _year, int _month, int _day);
    Date(int days){
        year = days / 365;
        days = days % 365;
        month = 1;
        while (days > daysInMonth(month)){
            days -= daysInMonth(month);
            month++;
        }
        day = days+1;
    }
    int daysInMonth(int month){
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
        if (month == 2) return 28;
        if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
        return 0;
    }
    bool operator == (Date b){
        Date a = *this;
        return a.day == b.day && a.year == b.year && a.month == b.month;
    } 
    bool operator != (Date b){
        Date a = *this;
        return a.day != b.day || a.year != b.year || a.month != b.month;
    }
    Date operator + (Date b){
        Date a = *this;
        int total = (a.year + b.year) * 365;
        for (int i = 1; i < a.month; ++i)
            total += daysInMonth(i);
        for (int i = 1; i < b.month; ++i)
            total += daysInMonth(i);

        return Date(total + a.day + b.day - 2);
    }
    int year;
    int month;
    int day;
    Date operator -(int d){
        Date a = *this;
        int total = (a.year) * 365;
        for (int i = 1; i < a.month; ++i)
            total += daysInMonth(i);
        return Date(total  + a.day - d - 1);
    }
    bool operator <(Date b){
        Date a = *this;
        if (a.year != b.year)
            return a.year < b.year;
        if (a.month != b.month)
            return a.month < b.month;
        if (a.day != b.day)
            return a.day < b.day;
        return false;
    }

    void print(){
        std::cout << year << "." << month << "." << day << "\n";
    }
    std::string toString(){
        return std::to_string(year) + "." + std::to_string(month) + "." + std::to_string(day);
    }



};



/*
bool operator <(Date a, Date b){
    if (a.year != b.year)
        return a.year < b.year;
    if (a.month != b.month)
        return a.month < b.month;
    if (a.day != b.day)
        return a.day < b.day;
    return false;
}

Date operator ++(Date a){
    return a + Date(0, 0, 1);
}*/
#endif // DATE_H
