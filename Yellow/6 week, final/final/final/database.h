#pragma once
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include "date.h"

class Database {
public:
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& stream) const;

	template <typename Predicate>
	int RemoveIf(const Predicate& predicate) {
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
	};

	template <typename Predicate>
	std::vector<std::pair<Date, std::string>> FindIf(const Predicate& predicate) const {
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

	std::pair<Date, std::string> Last(const Date& date) const;

private:
	std::map<Date, std::vector<std::string>> storage;
	std::map<Date, std::set<std::string>> checker;
};

std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::vector<std::string>>& pair);

bool operator<(const std::pair<Date, std::string>& left, const std::pair<Date, std::string>& right);

bool operator==(const std::pair<Date, std::string>& left, const std::pair<Date, std::string>& right);

std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::string>& pair_);
