#include "optimizer.h"
#include "TreeNode.h"

using TreeNodeType = TreeNode::TreeNodeType;

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

    // Try optimize right first because `0^0 = 1`
    if (node->right->getType() == TreeNodeType::CONSTANT) {
        auto value = dynamic_cast<ConstantNode *>(node->right)->value->getValue();

        if (value == 0) {
            switch (signature) {
                // expression [*] 0 -> 0
                case '*': {
                    auto constantZero = new ConstantNode(new Number(0));
                    parent->replaceChild(node, constantZero);
                    delete node;
                    break;
                }

                    // expression [+-] 0 -> expression
                case '+':
                case '-':
                    parent->replaceChild(node, node->left);

                    // Avoid deletion of left subtree because we still use it.
                    node->left = nullptr;
                    delete node;
                    break;

                    // expression ^ 0 -> 1
                case '^': {
                    auto constantOne = new ConstantNode(new Number(1));
                    parent->replaceChild(node, constantOne);
                    delete node;
                    break;
                }
            }
        } else if (value == 1) {
            switch (signature) {
                // expression [*/^] 1 -> expression
                case '*':
                case '/':
                case '^':
                    parent->replaceChild(node, node->left);
                    node->left = nullptr;
                    delete node;
                    break;
            }
        }
    } else if (node->left->getType() == TreeNodeType::CONSTANT) {
        auto value = dynamic_cast<ConstantNode *>(node->left)->value->getValue();

        if (value == 0) {
            switch (signature) {
                // 0 [*/^] expression -> 0
                case '*':
                case '/':
                case '^': {
                    auto constantZero = new ConstantNode(new Number(0));
                    parent->replaceChild(node, constantZero);
                    delete node;
                    break;
                }

                    // 0 [+-] expression -> expression
                case '+':
                case '-':
                    parent->replaceChild(node, node->right);
                    node->right = nullptr;
                    delete node;
                    break;
            }
        } else if (value == 1)
            switch (signature) {
                // 1 * expression -> expression
                case '*':
                    parent->replaceChild(node, node->right);
                    node->right = nullptr;
                    delete node;
                    break;

                    // 1 ^ expression -> 1
                case '^': {
                    auto constantOne = new ConstantNode(new Number(1));
                    parent->replaceChild(node, constantOne);
                    delete node;
                    break;
                }
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
    if (node->ifFalse != nullptr) {
        node->ifFalse->accept(this);
    }

    if (node->condition->getType() == TreeNodeType::CONSTANT) {
        auto value = dynamic_cast<ConstantNode *>(node->condition)->value->getValue();
        if (isTrue(value)) {
            parent->replaceChild(node, node->ifTrue);

            node->ifTrue = nullptr;
            delete node;
        } else if (node->ifFalse != nullptr) {
            parent->replaceChild(node, node->ifFalse);

            node->ifFalse = nullptr;
            delete node;
        } else {
            // Removing node from parent will cause shift of other nodes which is very inefficient.
            // It's better to just leave as is.
        }
    }

    stack.pop();
    return 0;
}
