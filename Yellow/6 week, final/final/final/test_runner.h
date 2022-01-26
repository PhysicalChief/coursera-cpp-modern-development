#pragma once
#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

class TestRunner
{
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name);
	~TestRunner();
private:
	int fail_count = 0;
};

template <class T>
ostream& operator << (ostream& os, const set<T>& s);
template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m);
template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p);
template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {});
void Assert(bool b, const string& hint);