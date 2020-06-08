#pragma once

#include <string>
#include <vector>
#include "token.h"
#include "visitor.h"

class TreeNode {
public:
    enum Type {
        STATEMENT_LIST, OPERATOR, VARIABLE, CONSTANT, ASSIGNMENT, BRANCH
    };

    virtual ~TreeNode() = default;

    virtual double accept(Visitor *visitor) = 0;

    [[nodiscard]] virtual bool isExpression() const = 0;

    virtual void replaceChild(TreeNode *value, TreeNode *replacement) = 0;

    [[nodiscard]] virtual Type getType() const = 0;
};

class StatementListNode : public TreeNode {
public:
    std::vector<TreeNode *> statements;

    ~StatementListNode() override {
        for (auto *statement : statements) {
            delete statement;
        }
    }

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    [[nodiscard]] bool isExpression() const override {
        return false;
    }

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] Type getType() const override {
        return STATEMENT_LIST;
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

    ~OperatorNode() override {
        delete left;
        delete right;
    }

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] Type getType() const override {
        return OPERATOR;
    }
};

class VariableNode : public ExpressionNode {
public:
    const std::string name;

    explicit VariableNode(std::string name) : name(std::move(name)) {};

    ~VariableNode() override = default;

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *value, TreeNode *replacement) override {
        throw std::invalid_argument("VariableNode doesn't have any children.");
    }

    [[nodiscard]] Type getType() const override {
        return VARIABLE;
    }
};

class ConstantNode : public ExpressionNode {
public:
    const Number *value;

    explicit ConstantNode(const Number *value) : value(value) {};

    ~ConstantNode() override {
        delete value;
    };

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *node, TreeNode *replacement) override {
        throw std::invalid_argument("ConstantNode doesn't have any children.");
    }

    [[nodiscard]] Type getType() const override {
        return CONSTANT;
    }
};

class AssignmentNode : public TreeNode {
public:
    VariableNode *variable;
    ExpressionNode *expression;

    AssignmentNode(VariableNode *variable, ExpressionNode *expression) : variable(variable), expression(expression) {}

    ~AssignmentNode() override {
        delete variable;
        delete expression;
    };

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] bool isExpression() const override {
        return false;
    }

    [[nodiscard]] Type getType() const override {
        return ASSIGNMENT;
    }
};

class BranchNode : public TreeNode {
public:
    ExpressionNode *condition;
    StatementListNode *ifTrue;
    StatementListNode *ifFalse;

    BranchNode(ExpressionNode *condition, StatementListNode *ifTrue, StatementListNode *ifFalse) :
            condition(condition), ifTrue(ifTrue), ifFalse(ifFalse) {}

    ~BranchNode() override {
        delete condition;
        delete ifTrue;
        delete ifFalse;
    };

    double accept(Visitor *visitor) override { return visitor->visit(this); };

    void replaceChild(TreeNode *value, TreeNode *replacement) override;

    [[nodiscard]] bool isExpression() const override {
        return false;
    }

    [[nodiscard]] Type getType() const override {
        return BRANCH;
    }
};
