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

    virtual double visit(StatementListNode *node) = 0;

    virtual double visit(ConstantNode *node) = 0;

    virtual double visit(VariableNode *node) = 0;

    virtual double visit(OperatorNode *node) = 0;

    virtual double visit(AssignmentNode *node) = 0;

    virtual double visit(BranchNode *node) = 0;

};