#pragma once

// avoiding circular dependency
class StatementListNode;
class ExpressionNode;
class AssignmentNode;
class BranchNode;

class Visitor {
public:

    double visit(StatementListNode *node) const;

    double visit(ExpressionNode *node) const;

    double visit(AssignmentNode *node) const;

    double visit(BranchNode *node) const;

};