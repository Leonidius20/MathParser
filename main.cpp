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
                        " if (1 + 5 * 6) "
                        " { blah =  4/ 2 + 4 - 4; }";

    auto tokens = Lexer(expression).tokenize();

    for (auto token : tokens) {
        cout << token->getType() << endl;
    }
    // auto tree = Parser(tokens).parse();
    Parser p(tokens);

    p.parse();
    // OptimizationVisitor().visit(tree);
    // auto value = ExpressionEvaluatorVisitor().visit(tree);

    Operator::destroyMap();
}
