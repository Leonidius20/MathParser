#include "Tree.h"
#include "visitor.h"
#include "evaluator.h"
#include "optimizer.h"

void Tree::optimize() {
    auto optimizer = new OptimizationVisitor();
    root->accept(optimizer);
}

void Tree::evaluate() {
    auto evaluator = new ExpressionEvaluatorVisitor();
    root->accept(evaluator);
}
