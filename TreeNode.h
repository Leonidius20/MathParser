#pragma once

#include <string>
#include <vector>
#include "token.h"

class TreeNode {
};

class StatementListNode : public TreeNode {
    std::vector<TreeNode> statements;
};

class ExpressionNode : public TreeNode {
};

class OperatorNode : public ExpressionNode {
    ExpressionNode *left;
    ExpressionNode *right;
    const Operator oper;

public:
    OperatorNode(const Operator &oper, ExpressionNode *left, ExpressionNode *right) : oper(oper), left(left),
                                                                                      right(right) {};
};

class VariableNode : public ExpressionNode {
    const std::string name;

public:
    explicit VariableNode(std::string name) : name(std::move(name)) {};
};

class ConstantNode : public ExpressionNode {
    const Number *value;

public:
    explicit ConstantNode(const Number *value) : value(value) {};
};

class AssignmentNode : public TreeNode {
    VariableNode *variable;
    ExpressionNode *expression;
};

class BranchNode : public TreeNode {
    ExpressionNode *condition;
    StatementListNode *ifTrue;
    StatementListNode *ifFalse;
};
