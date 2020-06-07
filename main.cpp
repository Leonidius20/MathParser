#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "token.h"
#include "calculator.h"
#include "TreeNode.h"

using namespace std;

int main(int argc, char *argv[]) {
    // TODO: fix ^ operator

    string expression = "blah = 4;"
                        " if (1 + 5 * 6 ^ 2) "
                        " { blah =  4/ 2 + 4 - 4 ^ 5; }";

    auto tokens = Lexer(expression).tokenize();
    auto tree = Parser(tokens).parse();
    // OptimizationVisitor().visit(tree);
    // auto value = ExpressionEvaluatorVisitor().visit(tree);

    Operator::destroyMap();
}
