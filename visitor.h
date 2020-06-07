#pragma once

// avoiding circular dependency
class StatementListNode;
class ConstantNode;
class VariableNode;
class OperatorNode;
class AssignmentNode;
class BranchNode;

class Visitor {
public:

    double visit(StatementListNode *node) const;

    double visit(ConstantNode *node) const;

    double visit(VariableNode *node) const;

    double visit(OperatorNode *node) const;

    double visit(AssignmentNode *node) const;

    double visit(BranchNode *node) const;

};