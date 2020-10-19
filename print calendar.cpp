#include <iostream>
using namespace std;
const int DAYS_OF_WEEK = 7;
const int DAYS_OF_JANUARY = 31;
const int DAYS_OF_FEBRUARY_LEAP = 29;
const int DAYS_OF_FEBRUARY_NOT_LEAP = 28;
const int DAYS_OF_MARCH = 31;
const int DAYS_OF_APRIL = 30;
const int DAYS_OF_MAY = 31;
const int DAYS_OF_JUNE = 30;
const int DAYS_OF_JULY = 31;
const int DAYS_OF_AUGUST = 31;
const int DAYS_OF_SEPTEMBER = 30;
const int DAYS_OF_OCTOBER = 31;
const int DAYS_OF_NOVEMBER = 30;
const int DAYS_OF_DECEMBER = 31;
int printMonthCalender(int numOfDays, int startingDay) {
    cout << "Mon" << '\t' << "Tue" << '\t' << "Wed" << '\t' << "Thr" << '\t'
         << "Fri" << '\t' << "Sat" << '\t' << "Sun" << endl;
    int daysOfFirstWeek = DAYS_OF_WEEK - startingDay + 1;
    for (int countSpace = 1; countSpace < startingDay; countSpace++) {
        cout << ' ' << '\t';
    }
    for (int countFirstWeek = 1; countFirstWeek <= daysOfFirstWeek; countFirstWeek++) {
        cout << countFirstWeek << '\t' ;
    }
    cout << endl;

    int extraWeeks;
    int lastDayInWeek;
    if ((numOfDays - daysOfFirstWeek) % DAYS_OF_WEEK == 0) {
        extraWeeks = (numOfDays - daysOfFirstWeek) / DAYS_OF_WEEK ;
    } else {
        extraWeeks = (numOfDays - daysOfFirstWeek) / DAYS_OF_WEEK + 1;
    }
    lastDayInWeek = numOfDays - daysOfFirstWeek - DAYS_OF_WEEK * (extraWeeks - 1);

    for (int countExtraWeeks = 1; countExtraWeeks <= extraWeeks; countExtraWeeks++) {
        for (int num = daysOfFirstWeek + 1 + DAYS_OF_WEEK * (countExtraWeeks - 1);
                 num <= daysOfFirstWeek + DAYS_OF_WEEK * countExtraWeeks && num <= numOfDays; num++) {
            cout << num << '\t' ;
        }
        cout << endl;
    }

    return lastDayInWeek;
}

bool leapYeaOrNot (int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return true;
    } else {return false;}
}

void printYearCalendar (int year, int startingDay) {
    cout << "January" << ' ' << year << endl;
    int lastDay;
    lastDay = printMonthCalender(DAYS_OF_JANUARY, startingDay);
    cout << endl;

    cout << "February" << ' ' << year << endl;
    int daysOfFebruary;
    if (leapYeaOrNot(year) == true) {daysOfFebruary = DAYS_OF_FEBRUARY_LEAP;}
    else {daysOfFebruary = DAYS_OF_FEBRUARY_NOT_LEAP;}
    int startDay;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(daysOfFebruary, startDay);
    cout << endl;

    cout << "March" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_MARCH, startDay);
    cout << endl;

    cout << "April" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_APRIL, startDay);
    cout << endl;

    cout << "May" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_MAY, startDay);
    cout << endl;

    cout << "June" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_JUNE, startDay);
    cout << endl;

    cout << "July" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_JULY, startDay);
    cout << endl;

    cout << "August" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_AUGUST, startDay);
    cout << endl;

    cout << "September" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_SEPTEMBER, startDay);
    cout << endl;

    cout << "October" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_OCTOBER, startDay);
    cout << endl;

    cout << "November" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_NOVEMBER, startDay);
    cout << endl;

    cout << "December" << ' ' << year << endl;
    if (lastDay == 7) {startDay = 1;}
    else {startDay = lastDay + 1;}
    lastDay = printMonthCalender(DAYS_OF_DECEMBER, startDay);
    cout << endl;
}

int main() {

    int inputYear, inputStartingDay;
    cout << "Please enter the year: ";
    cin >> inputYear;
    cout << "Please enter the starting of the year, e.g. 1 means Monday, 7 means Sunday: ";
    cin >> inputStartingDay;
    printYearCalendar(inputYear, inputStartingDay);
    return 0;
}
