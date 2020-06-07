#include <iostream>
#include <string>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "token.h"
#include "calculator.h"
#include "TreeNode.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "File to read not specified" << endl;
        return 0;
    }

    string file = argv[1];
    ifstream stream(file);
    if (!stream.is_open()) {
        cerr << "Could not read the file provided" << endl;
        return 0;
    }

    string line, expression;
    while (getline(stream, line)) expression.append(line);

    auto tokens = Lexer(expression).tokenize();
    auto tree = Parser(tokens).parse();
    // OptimizationVisitor().visit(tree);
    // auto value = ExpressionEvaluatorVisitor().visit(tree);

    Operator::destroyMap();
}
