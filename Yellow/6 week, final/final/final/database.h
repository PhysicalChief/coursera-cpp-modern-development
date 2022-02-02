#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <exception>
#include <algorithm>

#include "date.h"

class Database {
public:
    void Add(const Date& date, const std::string& event);
    void Print(std::ostream& stream) const;

    template <typename Predicate>
    int RemoveIf(const Predicate& predicate);

    template <typename Predicate>
    std::vector<std::pair<Date, std::string>> FindIf(const Predicate& predicate) const;

    std::pair<Date, std::string> Last(const Date& date) const;

private:
    std::map<Date, std::vector<std::string>> storage;
    std::map<Date, std::set<std::string>> checker;
};

std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::vector<std::string>>& pair);

bool operator<(const std::pair<Date, std::string>& left, const std::pair<Date, std::string>& right);

bool operator==(const std::pair<Date, std::string>& left, const std::pair<Date, std::string>& right);

std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::string>& pair_);
