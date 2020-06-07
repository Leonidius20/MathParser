#pragma once

#include <string>
#include <vector>
#include "token.h"
#include "visitor.h"

class TreeNode {
public:
    virtual double accept(const Visitor &visitor) = 0;
};

class StatementListNode : public TreeNode {
    std::vector<TreeNode> statements;
public:
    double accept(const Visitor &visitor) override { return visitor.visit(this); };
};

class ExpressionNode : public TreeNode {
public:
    double accept(const Visitor &visitor) override { return visitor.visit(this); };
};

class OperatorNode : public ExpressionNode {
    ExpressionNode *left;
    ExpressionNode *right;
    Operator *oper;

public:
    OperatorNode(Operator *oper, ExpressionNode *left, ExpressionNode *right) : oper(oper), left(left),
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
public:
    double accept(const Visitor &visitor) override { return visitor.visit(this); };
};

class BranchNode : public TreeNode {
    ExpressionNode *condition;
    StatementListNode *ifTrue;
    StatementListNode *ifFalse;
public:
    double accept(const Visitor &visitor) override { return visitor.visit(this); };
};
