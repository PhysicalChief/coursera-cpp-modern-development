#pragma once
#include "date.h"
#include <string>
#include <memory>

enum class LogicalOperation
{
	And,
	Or,
};

enum class Comparison {
	Less,
	LessOrEqual, 
	Greater, 
	GreaterOrEqual,
	Equal,
	NotEqual,
};

class Node
{
	virtual bool Evaluate() const = 0;
};

class EmptyNode : public Node {
	bool Evaluate(const Date& date, const std::string& event);
};

class DateComparisonNode : public Node {
public :
	DateComparisonNode(const Comparison& com, const Date& date);
	bool Evaluate(const Date& date, const std::string& event);
private:
	const Comparison comparison;
	const Date date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& com, const std::string& str);
	bool Evaluate(const Date& date, const std::string& event);
private:
	const Comparison comparison;
	const std::string event_name;
};

class LogicalOperationNode : public Node {
public:
	bool Evaluate(const Date& date, const std::string& event);
private:
	const LogicalOperation logical_operation;
	const std::shared_ptr<Node> left_node, right_node;
};