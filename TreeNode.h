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

public:
    virtual double evaluate() = 0; // TODO: generate implementations
};

class OperatorNode : public ExpressionNode {
    ExpressionNode *left;
    ExpressionNode *right;
    const Operator oper;

public:
    explicit OperatorNode(const Operator &oper) : oper(oper) {};
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

class AssigmentNode : public TreeNode {
    VariableNode *variable;
    ExpressionNode *expression;
};

class BranchNode : public TreeNode {
    ExpressionNode *condition;
    StatementListNode *ifTrue;
    StatementListNode *ifFalse;
};
