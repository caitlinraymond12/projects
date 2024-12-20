#include <iostream>
#include <string>

using namespace std;

const string months[] = 
{
    "January", "February", "March", "April", "May", "June", "July", "August", 
    "September", "October", "November", "December"
};

const string week_days[] = 
{
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

int find_month(const string& wanted, const int first) 
{
    if (months[first] == wanted)
        return first;
    return find_month(wanted, first + 1);
}

int month_length(const int month, const int year, const int days) 
{
    if (month < 0)
        return days;
    else 
    {
        if (month == 1) 
        {
            if (year % 4 == 0) 
            {
                if (year % 100 == 0) 
                {
                    if (year % 400 == 0) 
                    {
                        const int k = 29;
                        return month_length(month - 1, year, days + k);
                    }
                    else 
                    {
                        const int k = 28;
                        return month_length(month - 1, year, days + k);
                    }
                }
                else 
                {
                    const int k = 29;
                    return month_length(month - 1, year, days + k);
                }
            }
            else 
            {
                const int k = 28;
                return month_length(month - 1, year, days + k);
            }
        }
        else if (month == 0 || month == 2 || month == 4 || month == 6 || 
                 month == 7 || month == 9 || month == 11) 
        {
            const int k = 31;
            return month_length(month - 1, year, days + k);
        }
        else 
        {
            const int k = 30;
            return month_length(month - 1, year, days + k);
        }
    }
}

int single_month_length(const int month, const int year) 
{
    if (month == 1) 
    {
        if (year % 4 == 0) 
        {
            if (year % 100 == 0) 
            {
                if (year % 400 == 0)
                    return 29;
                else
                    return 28;
            }
            else
                return 29;
        }
        else
            return 28;
    }
    else if (month == 0 || month == 2 || month == 4 || month == 6 || 
             month == 7 || month == 9 || month == 11) 
        return 31;
    else 
        return 30;
}

int day_of_year(const int month, const int day, const int year) 
{
    if (month == 0)
        return day;
    return month_length(month - 1, year, 0) + day;
}

int day_ever(const int year, const int day_counting) 
{
    if (year < 0)
        return day_counting;
    else 
    {
        if (year % 4 == 0) 
        {
            if (year % 100 == 0) 
            {
                if (year % 400 == 0) 
                {
                    const int k = 366;
                    return day_ever(year - 1, day_counting + k);
                }
                else 
                {
                    const int k = 365;
                    return day_ever(year - 1, day_counting + k);
                }
            }
            else 
            {
                const int k = 366;
                return day_ever(year - 1, day_counting + k);
            }
        }
        else 
        {
            const int k = 365;
            return day_ever(year - 1, day_counting + k);
        }
    }
}

int day_of_week(const int day) 
{
    const int weekday = day % 7;
    if (weekday == 0 || weekday == 1 || weekday == 2)
        return weekday + 4;
    else
        return weekday - 3;
}

void month_calendar2(const int day, const int maxdays, const int space)
{
    if (day <= maxdays)
    {
        if (space > 20)
        {
            cout << endl;
            month_calendar2(day, maxdays, 0);
        }
        else 
        {
            if (day < 10) {
                cout << " " << day << " ";
                month_calendar2(day + 1, maxdays, space + 3);
            }
            else {
                cout << day << " ";
                month_calendar2(day + 1, maxdays, space + 3);
            }
        }
    }
    else
        cout << "\n";
}

void month_calendar1(const int weekday, const int monthlength, const int month, const int year) 
{
    cout << "    " << months[month] << " " << year << "\n";
    cout << "Mo" << " " << "Tu" << " " << "We" << " " << "Th" << " " << "Fr" << " " << "Sa" << " " << "Su";

    if (weekday == 0) 
    {
        cout << "\n";
        month_calendar2(1, monthlength, 0);
    }
    if (weekday == 1) 
    {
        cout << "\n" << "   ";
        month_calendar2(1, monthlength, 3);
    }
    if (weekday == 2) 
    {
        cout << "\n" << "      ";
        month_calendar2(1, monthlength, 6);
    }
    if (weekday == 3)
    {
        cout << "\n" << "         ";
        month_calendar2(1, monthlength, 9);
    }
    if (weekday == 4) 
    {
        cout << "\n" << "            ";
        month_calendar2(1, monthlength, 12);
    }
    if (weekday == 5)
    {
        cout << "\n" << "               ";
        month_calendar2(1, monthlength, 15);
    }
    if (weekday == 6)
    {
        cout << " \n" << "                  ";
        month_calendar2(1, monthlength, 18);
    }
}

void season(const int month, const int year) 
{
    const int year_day = day_of_year(month, 1, year);
    const int any_day_ever = day_ever(year - 1, 0) + year_day;
    const int weekday = day_of_week(any_day_ever);
    const int monthlength = single_month_length(month, year);
    month_calendar1(weekday, monthlength, month, year);
    cout << endl;
}

void user()
{
    
    while(true)
    {    
        cout << "Type a month: ";
        int month;
        cin >> month;
        if(month < 1 || month > 12 || cin.fail())
        {
            cout << "Not a valid input. Type a number between 1-12.\n";
            cin.clear();
            continue;
        }
        
        month--;  // Adjust to 0-based index
        cout << "Type a year: ";
        int year;
        cin >> year;
        cout << "\n";

        if (month == 0) 
        {
            season(month, year);
            season(month + 1, year);
        }
        else if (month == 11) 
        {
            season(month - 1, year);
            season(month, year);
        }
        else 
        {
            season(month - 1, year);
            season(month, year);
            season(month + 1, year);
        }
        cout << "\n";
    }
}

int main()
{
    user();
    return 0;
}

