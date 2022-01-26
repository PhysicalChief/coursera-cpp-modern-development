#pragma once
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

ostream& operator<<(ostream& stream, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);