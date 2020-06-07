#include <iostream>
#include <string>
#include "lexer.h"
#include "token.h"
#include "calculator.h"
#include "TreeNode.h"

using namespace std;

int main(int argc, char *argv[]) {

    /*if (argc < 2) {
        cerr << "Arithmetic expression is not specified" << endl;
        return 0;
    }*/

    string expression = "blah = 4;"
                        " if (1 + 5 * 6^3) "
                        " { blah =  4/ 2 + 4 - 4^3; }";
    //string expression;
    /*for (int i = 1; i < argc; i++) {
        expression.append(argv[i]);
    }*/

    auto tokens = Lexer(expression).tokenize();

    //ExpressionNode expr = *(parse(expression));
    /*try {
        expr = parse(expression);
        double result = compute(tokens);
        for (auto token : tokens) {
            if (token->isNumber()) delete token;
        }
        cout << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }*/

    Operator::destroyMap();
}
