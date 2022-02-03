
#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const {
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& com, const Date& date) : comparison(com), date(date) {}

bool DateComparisonNode::Evaluate(const Date& inDate, const std::string& event) const {
	if (comparison == Comparison::Equal) {
		return inDate == date;
	}	
	if (comparison == Comparison::Less) {
		return inDate < date;
	}
	if (comparison == Comparison::LessOrEqual) {
		return inDate <= date;
	}
	if (comparison == Comparison::Greater) {
	return inDate > date;
}
	if (comparison == Comparison::GreaterOrEqual) {
		return inDate >= date;
	}
	if (comparison == Comparison::NotEqual) {
		return inDate != date;
	}
	return false;
}

EventComparisonNode::EventComparisonNode(const Comparison& com, const std::string& str) : comparison(com), event_name(str) {}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
	if (comparison == Comparison::Equal) {
		return event == event_name;
	}
	if (comparison == Comparison::NotEqual) {
		return event != event_name;
	}
	if (comparison == Comparison::Less) {
		return event < event_name;
	}
	if (comparison == Comparison::LessOrEqual) {
		return event <= event_name;
	}
	if (comparison == Comparison::Greater) {
		return event > event_name;
	}
	if (comparison == Comparison::GreaterOrEqual) {
		return event >= event_name;
	}
	return false;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation log_op, std::shared_ptr<Node> left, std::shared_ptr<Node> right) :
	logical_operation(log_op), left_node(left), right_node(right) {};

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event_) const {
	if (logical_operation == LogicalOperation::And) {
		return left_node->Evaluate(date, event_) && right_node->Evaluate(date, event_);
	}
	if (logical_operation == LogicalOperation::Or) {
		return left_node->Evaluate(date, event_) || right_node->Evaluate(date, event_);
	}
	return false;
}
