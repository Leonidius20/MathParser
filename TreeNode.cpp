#include "TreeNode.h"

void StatementListNode::replaceChild(TreeNode *value, TreeNode *replacement) {
    for (int i = 0; i < statements.size(); ++i) {
        if (statements[i] == value) {
            statements[i] = replacement;
            return;
        }
    }
    throw std::invalid_argument("No child matching value found.");
}

void OperatorNode::replaceChild(TreeNode *value, TreeNode *replacement) {
    if (left == value) {
        left = dynamic_cast<ExpressionNode *>(replacement);
    } else if (right == value) {
        right = dynamic_cast<ExpressionNode *>(replacement);
    } else {
        throw std::invalid_argument("No child matching value found.");
    }
}

void AssignmentNode::replaceChild(TreeNode *value, TreeNode *replacement) {
    if (variable == value) {
        variable = dynamic_cast<VariableNode *>(replacement);
    } else if (expression == value) {
        expression = dynamic_cast<ExpressionNode *>(replacement);
    } else {
        throw std::invalid_argument("No child matching value found.");
    }
}

void BranchNode::replaceChild(TreeNode *value, TreeNode *replacement) {
    if (condition == value) {
        condition = dynamic_cast<ExpressionNode *>(replacement);
    } else if (ifTrue == value) {
        ifTrue = dynamic_cast<StatementListNode *>(replacement);
    } else if (ifFalse != nullptr && ifFalse == value) {
        ifFalse = dynamic_cast<StatementListNode *>(replacement);
    } else {
        throw std::invalid_argument("No child matching value found.");
    }
}
