
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
using namespace std;

struct Date {
	int day;
	int month;
	int year;
}today, date;

void Take_today() {
	time_t now = time(NULL);
	tm* ltm = localtime(&now);
	today.day = ltm->tm_mday;
	today.month = ltm->tm_mon + 1;
	today.year = ltm->tm_year + 1900;
}

void Take_date() {
	while (true) {
		cout << "Enter the date you want calculate:(dd mm yyyy): ";
		cin >> date.day >> date.month >> date.year;

		if (date.month >= 1 && date.month <= 12) {
			if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12) {
				if (date.day >= 1 && date.day <= 31) {
					break;
				}
			}
			if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
				if (date.day >= 1 && date.day <= 30) {
					break;
				}
			}
			if (date.month == 2) {
				if ((date.year % 4 == 0) && (date.year % 100 != 0) || (date.year % 400 == 0)) {
					if (date.day >= 1 && date.day <= 29) {
						break;
					}
				}
				else {
					if (date.day >= 1 && date.day <= 28) {
						break;
					}
				}
			}
		}
		cout << "You entered invalid date. Please try again...\n\n";
	}
}

void Write_date(Date t) {
	string dt = "";
	if (t.day < 10)
	{
		dt = dt + '0';
		dt = dt + to_string(t.day);
	}
	else
	{
		dt = dt + to_string(t.day);
	}

	if (t.month < 10)
	{
		dt = dt + "/0";
		dt = dt + to_string(t.month);
	}
	else
	{
		dt = dt + "/" + to_string(t.month);
	}
	if (t.year < 0) {
		dt = "M.O." + dt;
		t.year *= -1;
	}
	dt = dt + "/" + to_string(t.year);

	cout << dt;
}

int Count(Date t1, Date t2) {
	int counter = 0;
	while (true) {
		if ((t1.year == t2.year)&(t1.day == t2.day) &(t1.month == t2.month)) {
			break;
		}
		t1.day++;
		counter++;
		if (t1.day >= 31 && (t1.month == 4 || t1.month == 6 || t1.month == 9 || t1.month == 11)) {
			t1.day = 1;
			t1.month++;
		}
		else if (t1.day >= 32 && (t1.month == 1 || t1.month == 3 || t1.month == 5 || t1.month == 7 || t1.month == 8 || t1.month == 10 || t1.month == 12)) {
			t1.day = 1;
			t1.month++;
		}
		else if (t1.month == 2) {
			if ((t1.day >= 30) && (t1.year % 4 == 0 && t1.year % 100 != 0 || t1.year % 400 == 0)) {
				t1.day = 1;
				t1.month++;
			}
			else if ((t1.day >= 29) && !(t1.year % 4 == 0 && t1.year % 100 != 0 || t1.year % 400 == 0)) {
				t1.day = 1;
				t1.month++;
			}
		}
		if (t1.month >= 13) {
			t1.month = 1;
			t1.year++;
		}
	}
	return counter;
}

int Calc_Date(Date bt, Date t) {
	bool flag;
	if (bt.year > t.year)
	{
		flag = false;
	}
	else if (bt.year == t.year)
	{
		if (bt.month > t.month)
		{
			flag = false;
		}
		else if (bt.month == t.month)
		{
			if (bt.day > t.day)
			{
				flag = false;
			}
			else if (bt.day == t.day)
			{
				flag = false; //Girilen gün bugün ile aynýysa ???
			}
			else
			{
				flag = true;
			}
		}
		else
		{
			flag = true;
		}
	}
	else
	{
		flag = true;
	}
	if (flag) {
		return Count(today, t);
	}
	else {
		return (-1 * Count(t, today));
	}
}

string Date_Finder(Date t) {
	/*if (t.year < 0)
		t.year *= -1;*/
	int a[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }, gun_kodu;
	t.year -= t.month < 3;
	gun_kodu = (t.year + t.year / 4 - t.year / 100 + t.year / 400 + a[t.month - 1] + t.day) % 7;
	switch (gun_kodu)
	{
	case 1:return "Monday"; break;
	case 2:return "Tuesday"; break;
	case 3:return "Wednesday"; break;
	case 4:return "Thursday"; break;
	case 5:return "Friday"; break;
	case 6:return "Saturday"; break;
	case 0:return "Sunday";  break;
	default:return " Invalid "; break;
	}
}

int main() {
	Take_today();
	Take_date();
	cout << "\nToday's date: ";
	Write_date(today);
	cout << endl;
	cout << "Date to be Calculated : ";
	Write_date(date);
	cout << endl << endl;
	int counter = Calc_Date(today, date);

	if (counter < 0)
		cout << "Entered date is on " << Date_Finder(date) << " " << -1 * counter << " days ago.";
	else
		cout << "Entered date is on " << Date_Finder(date) << " after " << counter << " days.";

	system("pause>null");
	return 0;
}