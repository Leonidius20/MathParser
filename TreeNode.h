#pragma once

#include <string>
#include <vector>
#include "token.h"
#include "visitor.h"

enum TreeNodeType {
    statement, operatorNode, variable, constant, assignment, branch
};

class TreeNode {
public:
    virtual double accept(Visitor *visitor) = 0;

    [[nodiscard]] virtual bool isExpression() const = 0;

    virtual void replaceChild(TreeNode *value, TreeNode *replacement) = 0;

    [[nodiscard]] virtual TreeNodeType getType() const = 0;
};

class StatementListNode : public TreeNode {
public:
    std::vector<TreeNode *> statements;

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    [[nodiscard]] bool isExpression() const override {
        return false;
    }

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] TreeNodeType getType() const override {
        return statement;
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

    OperatorNode(Operator *oper, ExpressionNode *left, ExpressionNode *right) :
            oper(oper), left(left), right(right) {};

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] TreeNodeType getType() const override {
        return operatorNode;
    }
};

class VariableNode : public ExpressionNode {
public:
    const std::string name;

    explicit VariableNode(std::string name) : name(std::move(name)) {};

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *value, TreeNode *replacement) override {
        throw std::invalid_argument("VariableNode doesn't have any children.");
    }

    [[nodiscard]] TreeNodeType getType() const override {
        return variable;
    }
};

class ConstantNode : public ExpressionNode {
public:
    const Number *value;

    explicit ConstantNode(const Number *value) : value(value) {};

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *node, TreeNode *replacement) override {
        throw std::invalid_argument("ConstantNode doesn't have any children.");
    }

    [[nodiscard]] TreeNodeType getType() const override {
        return constant;
    }
};

class AssignmentNode : public TreeNode {
public:
    VariableNode *variable;
    ExpressionNode *expression;

    AssignmentNode(VariableNode *variable, ExpressionNode *expression) : variable(variable), expression(expression) {}

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    [[nodiscard]] bool isExpression() const override {
        return false;
    }

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] TreeNodeType getType() const override {
        return assignment;
    }
};

class BranchNode : public TreeNode {
public:
    ExpressionNode *condition;
    StatementListNode *ifTrue;
    StatementListNode *ifFalse;

    BranchNode(ExpressionNode *condition, StatementListNode *ifTrue, StatementListNode *ifFalse) :
            condition(condition), ifTrue(ifTrue), ifFalse(ifFalse) {}

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    [[nodiscard]] bool isExpression() const override {
        return false;
    }

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] TreeNodeType getType() const override {
        return branch;
    }
};
