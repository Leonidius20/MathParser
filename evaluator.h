#pragma once

#include "visitor.h"

class ExpressionEvaluatorVisitor : public Visitor {
    std::unordered_map<std::string, double> variablesTable;

    static bool isTrue(double value) { return value != 0; }

public:
    double visit(StatementListNode *node) override;

    double visit(ConstantNode *node) override;

    double visit(VariableNode *node) override;

    double visit(OperatorNode *node) override;

    double visit(AssignmentNode *node) override;

    double visit(BranchNode *node) override;
};
