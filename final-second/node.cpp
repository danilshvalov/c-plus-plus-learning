
#include "node.h"
DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}
EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string& inputEvent) : cmp_(cmp), event_(inputEvent) {}
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) : op_(op), lhs_(lhs), rhs_(rhs) {}

bool Node::Evaluate(const Date& inputDate, const std::string& inputEvent) {
    return false;
}
bool DateComparisonNode::Evaluate(const Date& inputDate, const std::string& inputEvent) {
    switch (cmp_) {
    case Less:
        return inputDate < date_;
    case LessOrEqual:
        return (inputDate < date_ || inputDate == date_);
    case Greater:
        return inputDate > date_;
    case GreaterOrEqual:
        return (inputDate > date_ || inputDate == date_);
    case Equal:
        return date_ == inputDate;
    case NotEqual:
        return !(date_ == inputDate);
    }
    return false;
}
bool EventComparisonNode::Evaluate(const Date& inputDate, const std::string& inputEvent) {
    switch (cmp_) {
    case Equal:
        return event_ == inputEvent;
    case NotEqual:
        return event_ != inputEvent;
    }
    return false;
}
bool LogicalOperationNode::Evaluate(const Date& inputDate, const std::string& inputEvent) {
    switch (op_) {
    case And:
        return (lhs_->Evaluate(inputDate, inputEvent) && rhs_->Evaluate(inputDate, inputEvent));
    case Or:
        return (lhs_->Evaluate(inputDate, inputEvent) || rhs_->Evaluate(inputDate, inputEvent));
    }
    return false;
}