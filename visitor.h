#pragma once

#include <unordered_map>
#include "stack.h"

// avoiding circular dependency
class TreeNode;

class StatementListNode;

class ExpressionNode;

class ConstantNode;

class VariableNode;

class OperatorNode;

class AssignmentNode;

class BranchNode;

class Visitor {
public:

    virtual double visit(StatementListNode *node) = 0;

    virtual double visit(ConstantNode *node) = 0;

    virtual double visit(VariableNode *node) = 0;

    virtual double visit(OperatorNode *node) = 0;

    virtual double visit(AssignmentNode *node) = 0;

    virtual double visit(BranchNode *node) = 0;

};

class ExpressionEvaluatorVisitor : public Visitor {
    std::unordered_map<std::string, double> variablesTable;

public:
    double visit(StatementListNode *node) override;

    double visit(ConstantNode *node) override;

    double visit(VariableNode *node) override;

    double visit(OperatorNode *node) override;

    double visit(AssignmentNode *node) override;

    double visit(BranchNode *node) override;
};

class OptimizationVisitor : public Visitor {
    Stack<TreeNode *> stack;

public:
    double visit(StatementListNode *node) override;

    double visit(ConstantNode *node) override;

    double visit(VariableNode *node) override;

    double visit(OperatorNode *node) override;

    double visit(AssignmentNode *node) override;

    double visit(BranchNode *node) override;
};
