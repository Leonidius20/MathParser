#include "Tree.h"
#include "visitor.h"

void Tree::optimize() {
    auto optimizer = new OptimizationVisitor();
    root->accept(optimizer);
}

void Tree::evaluate() {
    auto evaluator = new ExpressionEvaluatorVisitor();
    root->accept(evaluator);
}
