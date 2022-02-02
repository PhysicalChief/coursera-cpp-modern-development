#include "database.h"

void Database::Add(const Date& date, const std::string& event_) {

	const size_t count_elements = checker.size();

	checker[date].insert(event_);

	if (checker.size() > count_elements) {
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

template<typename Predicate>
int Database::RemoveIf(const Predicate& predicate) {
	int remove_count = 0;
	std::map<Date, std::vector<std::string>> tmp_storage;
	std::map<Date, std::set<std::string>> tmp_unset;

	for (auto& pair : storage) {
		const auto border = stable_partition(pair.second.begin(), pair.second.end(),
			[predicate, pair](const auto& element) {
				return predicate(pair.first, element);
			});
		size_t size_vector = pair.second.size();
		if (border == pair.second.end()) {
			remove_count += size_vector;
		}
		else {
			tmp_storage[pair.first] = std::vector<std::string>(border, pair.second.end());
			tmp_unset[pair.first] = std::set<std::string>(border, pair.second.end());
			remove_count += size_vector - tmp_storage[pair.first].size();
		}
	}
	storage = tmp_storage;
	checker = tmp_unset;

	return remove_count;
}

template<typename Predicate>
std::vector<std::pair<Date, std::string>> Database::FindIf(const Predicate& predicate) const
{
	std::map<Date, std::vector<std::string>> tmp;
	std::vector<std::pair<Date, std::string>> result;

	for (const auto& pair_ : storage)
	{
		std::vector<std::string> tmp_vec;

		std::copy_if(pair_.second.begin(), pair_.second.end(), back_inserter(tmp_vec),
			[predicate, pair_](const auto& item)
			{
				return predicate(pair_.first, item);
			});

		if (tmp_vec.size() != 0)
		{
			tmp[pair_.first] = tmp_vec;
		}
	}

	for (const auto& pair_ : tmp)
	{
		for (const std::string& item : pair_.second)
		{
			result.push_back(make_pair(pair_.first, item));
		}
	}

	return result;
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