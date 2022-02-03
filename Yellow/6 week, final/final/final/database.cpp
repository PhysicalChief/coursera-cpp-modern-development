#include "database.h"

#include <algorithm>
#include <iostream>

void Database::Add(const Date& date, const std::string& event_) {

	const size_t count_elements = checker[date].size();

	checker[date].insert(event_);

	if (checker[date].size() > count_elements) {
		storage[date].push_back(event_);
	}
}

void Database::Print(std::ostream& out) const {
	for (const auto& pair_ : storage) {
		for (const auto& element : pair_.second) {
			out << pair_.first << " " << element << std::endl;
		}
	}
}

std::pair<Date, std::string> Database::Last(const Date& date) const {
	if (storage.empty()) {
		throw std::invalid_argument("No entries");
	}
	auto upper_date = storage.upper_bound(date);
	if (upper_date == storage.begin()) {
		throw std::invalid_argument("No entries");
	}
	--upper_date;
	return make_pair(upper_date->first, upper_date->second.back());
}

std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::vector<std::string>>& pair_)
{
	for (const auto& item : pair_.second)
	{
		os << pair_.first << " " << item << std::endl;
	}

	return os;
}


bool operator<(const std::pair<Date, std::string>& left, const std::pair<Date, std::string>& right)
{
	return left.first < right.first;
}


bool operator==(const std::pair<Date, std::string>& left, const std::pair<Date, std::string>& right)
{
	return left.first == right.first && right.second == left.second;
}


std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::string>& pair)
{
	os << pair.first << " " << pair.second;

	return os;
}