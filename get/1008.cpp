#include <iostream>
#include <string>

using namespace std;

int monthdays[2][12] = {
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int tradedyasoneyear[2][7] = {
	{252,252,253,254,254,253,252},
	{253,254,255,255,253,252,253}
};

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getWeekNumber(int year, int month, int day)
{
	if (month == 1 || month == 2) {
		year--;
		month += 12;
	}
	return ((day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7);
}

int deleteTradeDaysOneYear(int start[3], int end[3])
{
	int result = 0;
	if (start[1] == 1 && start[2] == 1)
		result += (getWeekNumber(start[0], 1, 1) <= 4);
	if (start[1] <= 5 && end[1] >= 5)
		if (start[1] < 5 && end[1] > 5)
			for (int i = 1; i <= 3; i++)
				result += (getWeekNumber(start[0], 5, i) <= 4);
		else if(start[1] == 5)
			for(int i = start[1]; i <= 3; i++)
				result += (getWeekNumber(start[0], 5, i) <= 4);
		else {
			for (int i = 1; i <= ((3 <= end[1])?3:end[1]) ; i++)
				result += (getWeekNumber(start[0], 5, i) <= 4);
		}
	if (start[1] <= 10 && end[1] >= 10)
		if (start[1] < 10 && end[1] > 10)
			for (int i = 1; i <= 7; i++)
				result += (getWeekNumber(start[0], 10, i) <= 4);
		else if (start[1] == 10)
			for (int i = start[1]; i <= 7; i++)
				result += (getWeekNumber(start[0], 10, i) <= 4);
		else {
			for (int i = 1; i <= ((7 <= end[1]) ? 7 : end[1]); i++)
				result += (getWeekNumber(start[0], 10, i) <= 4);
		}
	return result;
}

int getTradeDaysOneYear(int start[3], int end[3])
{
	int tradedays = 0;
	if (start[1] == end[1]) {
		tradedays += (end[2] - start[2] + 1) / 7 * 5;
		int week = getWeekNumber(end[0], end[1], end[2]) + 7;
		int num = (end[2] - start[2] + 1) % 7;
		for (int i = 0; i < num; i++) {
			if (week != 5 && week != 6 && week != 12 && week != 13)
				tradedays++;
			week--;
		}
		switch (start[1]) {
		case 1:
			tradedays -= (start[2] == 1 && getWeekNumber(start[0], 1, 1) <= 4); 
			break;
		case 5:
			for (int i = 1; i <= 3; i++)
				tradedays -= (getWeekNumber(start[0], 5, i) <= 4);
			break;
		case 10:
			for (int i = 1; i <= 7; i++)
				tradedays -= (getWeekNumber(start[0], 10, i) <= 4);
			break;
		default:
			break;
	}
		return tradedays;
	}
	else {
		int leap = isLeapYear(start[0]), days = 0;
		for (int i = start[1]; i < end[1]; i++) {
			days += monthdays[leap][i - 1];
		}
		days = days - start[2] + 1 + end[2];
		tradedays += days / 7 * 5;
		int week = getWeekNumber(end[0], end[1], end[2]) + 7;
		int num = days % 7;
		for (int i = 0; i < num; i++) {
			if (week != 5 && week != 6 && week != 12 && week != 13)
				tradedays++;
			week--;
		}
		tradedays -= deleteTradeDaysOneYear(start, end);
		return tradedays;
	}
}

int getTradeDays(int start[3], int end[3])
{
	if (start[0] == end[0])
		return getTradeDaysOneYear(start, end);
	else {
		int tradedays = 0;
		int endyear[3] = { start[0], 12, 31 };
		tradedays += getTradeDaysOneYear(start, endyear);
		int startyear[3] = {end[0], 1, 1};
		tradedays += getTradeDaysOneYear(startyear, end);
		for (int year = start[0] + 1; year < end[0]; year++) {
			tradedays += tradedyasoneyear[isLeapYear(year)][getWeekNumber(year, 1, 1)];
		}
		return tradedays;
	}
}
int main()
{
	int i, number;
	int start[3], end[3];
	string date;
	cin >> number;
	for (i = 0; i < number; i++) {
		cin >> date;
		start[0] = stoi(date.substr(0, 4));
		start[1] = stoi(date.substr(5, 2));
		start[2] = stoi(date.substr(8, 2));
		cin >> date;
		end[0] = stoi(date.substr(0, 4));
		end[1] = stoi(date.substr(5, 2));
		end[2] = stoi(date.substr(8, 2));
		cout << getTradeDays(start, end) << endl;
	}
	return 0;
}