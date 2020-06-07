#include "visitor.h"
#include "TreeNode.h"

double Visitor::visit(StatementListNode *node) const {
    return 0;
}

double Visitor::visit(AssignmentNode *node) const {
    return 0;
}

double Visitor::visit(BranchNode *node) const {
    return 0;
}

double Visitor::visit(OperatorNode *node) const {
    auto v1 = node->left->accept(*this);
    auto v2 = node->right->accept(*this);
    return node->oper->apply(v1, v2);
}

double Visitor::visit(VariableNode *node) const {
    return 0;
}

double Visitor::visit(ConstantNode *node) const {
    return 0;
}
