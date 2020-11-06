#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

#ifndef __CONDITION_PARSER_H__
#define __CONDITION_PARSER_H__

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
#endif // __CONDITION_PARSER_H__