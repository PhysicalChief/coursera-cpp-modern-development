#pragma once
#include <sstream>
#include <iomanip>


class Date
{
public:
	Date(int new_year, int new_month, int new_day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

Date ParseDate(const std::istringstream& is);

std::ostream& operator<<(std::ostream& stream, const Date& date);