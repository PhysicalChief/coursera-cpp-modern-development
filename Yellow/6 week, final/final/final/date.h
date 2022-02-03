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
	Date& operator=(const Date& other);
private:
	int year;
	int month;
	int day;
};

Date ParseDate(std::istream& is);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

std::ostream& operator<<(std::ostream& stream, const Date& date);