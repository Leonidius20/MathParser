#include <iostream>
#include <string>
#include <fstream>
#include "lexer.h"
#include "parser.h"

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

    try {
        auto tokens = Lexer(expression).tokenize();
        auto tree = Parser(tokens).parse();
        tree.optimize();
        tree.evaluate();
    } catch (const invalid_argument &e) {
        cerr << e.what() << endl;
    }

    Operator::destroyMap();
    Token::destroyMap();
}
