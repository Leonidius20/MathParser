#include "visitor.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;

bool isTrue(double value) { return value != 0; }

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

    for (TreeNode *statement : node->statements) {
        statement->accept(this);
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered" // Ignore "not all switch paths considered (add default)"

double OptimizationVisitor::visit(OperatorNode *node) {
    TreeNode *parent = stack.peek();

    // Try to optimize children first.
    stack.push(node);
    node->left->accept(this);
    node->right->accept(this);
    stack.pop();

    char signature = node->oper->getSignature();
    auto constantZero = new ConstantNode(new Number(0));
    auto constantOne = new ConstantNode(new Number(1));

    // Try optimize right first because `0^0 = 1`
    if (node->right->getType() == constant) {
        auto value = dynamic_cast<ConstantNode *>(node->right)->value->getValue();

        if (value == 0) {
            switch (signature) {
                // expression [*] 0 -> 0
                case '*':
                    parent->replaceChild(node, constantZero);
                    break;

                    // expression [+-] 0 -> expression
                case '+':
                case '-':
                    parent->replaceChild(node, node->left);
                    break;

                    // expression ^ 0 -> 1
                case '^':
                    parent->replaceChild(node, constantOne);
                    break;
            }
        } else if (value == 1) {
            switch (signature) {
                // expression [*/^] 1 -> expression
                case '*':
                case '/':
                case '^':
                    parent->replaceChild(node, node->left);
                    break;
            }
        }
    } else if (node->left->getType() == constant) {
        auto value = dynamic_cast<ConstantNode *>(node->left)->value->getValue();

        if (value == 0) {
            switch (signature) {
                // 0 [*/^] expression -> 0
                case '*':
                case '/':
                case '^':
                    parent->replaceChild(node, constantZero);
                    break;

                    // 0 [+-] expression -> expression
                case '+':
                case '-':
                    parent->replaceChild(node, node->right);
                    break;
            }
        } else if (value == 1)
            switch (signature) {
                // 1 * expression -> expression
                case '*':
                    parent->replaceChild(node, node->right);
                    break;

                    // 1 ^ expression -> 1
                case '^':
                    parent->replaceChild(node, constantOne);
                    break;
            }
    }

    return 0;
}

#pragma clang diagnostic pop

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

    if (node->condition->getType() == constant) {
        auto value = dynamic_cast<ConstantNode *>(node->condition)->value->getValue();
        if (isTrue(value)) {
            parent->replaceChild(node, node->ifTrue);
        } else if (node->ifFalse != nullptr) {
            parent->replaceChild(node, node->ifFalse);
        } else {
            // TODO: remove BranchNode from parent?
        }
    }

    stack.pop();
    return 0;
}
