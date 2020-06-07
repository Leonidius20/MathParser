#include "evaluator.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;

double ExpressionEvaluatorVisitor::visit(StatementListNode *node) {
    for (TreeNode *statement : node->statements) {
        auto result = statement->accept(this);

        if (statement->isExpression()) {
            cout << result << endl; // TODO: print expression.
        }
    }

    return 0;
}

double ExpressionEvaluatorVisitor::visit(ConstantNode *node) {
    const Number *number = node->value;
    return number->getValue();
}

double ExpressionEvaluatorVisitor::visit(VariableNode *node) {
    std::string name = node->name;
    return variablesTable.at(name);
}

double ExpressionEvaluatorVisitor::visit(OperatorNode *node) {
    auto leftResult = node->left->accept(this);
    auto rightResult = node->right->accept(this);
    return node->oper->apply(leftResult, rightResult);
}

double ExpressionEvaluatorVisitor::visit(AssignmentNode *node) {
    auto variableName = node->variable->name;
    auto result = node->expression->accept(this);
    variablesTable[variableName] = result;
    return result;
}

double ExpressionEvaluatorVisitor::visit(BranchNode *node) {
    auto condition = node->condition->accept(this);

    if (isTrue(condition)) {
        node->ifTrue->accept(this);
    } else if (node->ifFalse != nullptr) {
        node->ifFalse->accept(this);
    }

    return 0;
}
