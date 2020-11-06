
#include "date.h"
#include <memory>

#ifndef __NODE_H__
#define __NODE_H__

enum Comparison {
    Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual
};
enum LogicalOperation {
    And, Or
};
class Node {
private:
public:
    virtual bool Evaluate(const Date& inputDate, const std::string& inputEvent);
};
class DateComparisonNode : public Node {
private:
    const Comparison cmp_;
    Date date_;
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& inputDate, const std::string& inputEvent) override;
};
class EventComparisonNode : public Node {
private:
    const Comparison cmp_;
    std::string event_;
public:
    EventComparisonNode(const Comparison& cmp, const std::string& inputEvent);
    bool Evaluate(const Date& inputDate, const std::string& inputEvent) override;
};
class LogicalOperationNode : public Node {
private:
    const LogicalOperation op_;
    std::shared_ptr<Node> lhs_, rhs_;
public:
    LogicalOperationNode(const LogicalOperation& op, std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs);
    bool Evaluate(const Date& inputDate, const std::string& inputEvent) override;
};
class EmptyNode : public Node {};


#endif // __NODE_H__