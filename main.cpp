#include <iostream>
#include <string>
#include "shunting_yard.h"
#include "token.h"
#include "calculator.h"
#include "TreeNode.h"

using namespace std;

int main(int argc, char *argv[]) {
    char c;
    cin >> c;

    if (argc < 2) {
        cerr << "Arithmetic expression is not specified" << endl;
        return 0;
    }

    string expression;
    for (int i = 1; i < argc; i++) {
        expression.append(argv[i]);
    }

    ExpressionNode expr = *(parse(expression));
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
