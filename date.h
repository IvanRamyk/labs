#ifndef DATE_H
#define DATE_H





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
        day = days++;
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
    Date operator + (Date b){
        Date a = *this;
        return Date((a.year + b.year) * 365 + daysInMonth(a.month) + daysInMonth(b.month) + a.day + b.day);
    }
    int year;
    int month;
    int day;
    Date operator -(int d){
        Date a = *this;
        return Date((a.year) * 365 + daysInMonth(a.month) + a.day - d);
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
