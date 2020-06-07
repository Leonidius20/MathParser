#pragma once

#include <string>
#include <vector>
#include "token.h"
#include "visitor.h"

class TreeNode {
public:
    virtual double accept(const Visitor &visitor) = 0;

    [[nodiscard]] virtual bool isExpression() const = 0;
};

class StatementListNode : public TreeNode {
public:
    std::vector<TreeNode> statements;

    double accept(const Visitor &visitor) override { return visitor.visit(this); };

    [[nodiscard]] bool isExpression() const override {
        return false;
    }
};

class ExpressionNode : public TreeNode {
public:
    [[nodiscard]] bool isExpression() const override {
        return true;
    }
};

class OperatorNode : public ExpressionNode {
public:
    ExpressionNode *left;
    ExpressionNode *right;
    const Operator *oper;

    OperatorNode(Operator *oper, ExpressionNode *left, ExpressionNode *right) : oper(oper), left(left),
                                                                                right(right) {};

    double accept(const Visitor &visitor) override { return visitor.visit(this); };
};

class VariableNode : public ExpressionNode {
public:
    const std::string name;

    explicit VariableNode(std::string name) : name(std::move(name)) {};

    double accept(const Visitor &visitor) override { return visitor.visit(this); };
};

class ConstantNode : public ExpressionNode {
public:
    const Number *value;

    explicit ConstantNode(const Number *value) : value(value) {};

    double accept(const Visitor &visitor) override { return visitor.visit(this); };
};

class AssignmentNode : public TreeNode {
public:
    VariableNode *variable;
    ExpressionNode *expression;

    AssignmentNode(VariableNode *variable, ExpressionNode *expression) : variable(variable), expression(expression) {}

    double accept(const Visitor &visitor) override { return visitor.visit(this); };

    [[nodiscard]] bool isExpression() const override {
        return false;
    }
};

class BranchNode : public TreeNode {
public:
    ExpressionNode *condition;
    StatementListNode *ifTrue;
    StatementListNode *ifFalse;

    BranchNode(ExpressionNode *condition, StatementListNode *ifTrue, StatementListNode *ifFalse) : condition(condition),
                                                                                                   ifTrue(ifTrue),
                                                                                                   ifFalse(ifFalse) {}

    double accept(const Visitor &visitor) override { return visitor.visit(this); };

    [[nodiscard]] bool isExpression() const override {
        return false;
    }
};
