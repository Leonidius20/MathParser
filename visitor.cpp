#include "visitor.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;

double ExpressionEvaluatorVisitor::visit(StatementListNode *node) {
    for (TreeNode &statement : node->statements) {
        auto result = statement.accept(this);

        if (statement.isExpression()) {
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
    string name = node->name;
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

//===================== OptimizationVisitor =============================================

double OptimizationVisitor::visit(StatementListNode *node) {
    stack.push(node);

    for (TreeNode &statement : node->statements) {
        statement.accept(this);
    }

    stack.pop();
    return 0;
}

double OptimizationVisitor::visit(ConstantNode *node) {
    // There is nothing to optimize.
    return 0;
}

double OptimizationVisitor::visit(VariableNode *node) {
    // There is nothing to optimize.
    return 0;
}

double OptimizationVisitor::visit(OperatorNode *node) {
    TreeNode *parent = stack.peek();
    stack.push(node);

    // TODO:
    //   - 0 [*/] expression -> 0
    //   - expression [*] 0 -> 0
    //   - 0 [+-] expression -> expression
    //   - expression [+-] 0 -> expression
    //   - expression [*/] 1 -> expression

    stack.pop();
    return 0;
}

double OptimizationVisitor::visit(AssignmentNode *node) {
    stack.push(node);

    // Try to optimize expression.
    node->expression->accept(this);

    stack.pop();
    return 0;
}

double OptimizationVisitor::visit(BranchNode *node) {
    TreeNode *parent = stack.peek();
    stack.push(node);

    node->condition->accept(this);
    node->ifTrue->accept(this);
    node->ifFalse->accept(this);

    // TODO: if condition is constant...

    stack.pop();
    return 0;
}
