#include "visitor.h"
#include "TreeNode.h"

double Visitor::visit(StatementListNode *node) const {
    return 0;
}

double Visitor::visit(ExpressionNode *node) const {
    // recursively calling accept() on children
    return 0;
}

double Visitor::visit(AssignmentNode *node) const {
    return 0;
}

double Visitor::visit(BranchNode *node) const {
    return 0;
}
