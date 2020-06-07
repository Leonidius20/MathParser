#include <vector>
#include <string>
#include "token.h"
#include "stack.h"
#include "TreeNode.h"
#include "shunting_yard.h"

using namespace std;

const char NOT_FOUND = -1;

bool shouldParseAsOperator(const string &expression, int position);

ExpressionNode *parseExpression(const string &expression) {
    Stack<ExpressionNode *> expressionStack;
    Stack<MathToken *> operatorStack;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isspace(c)) continue;

        if (shouldParseAsOperator(expression, i)) {
            auto oper = Operator::get(c);
            while (!operatorStack.empty()) {
                auto token = operatorStack.peek();
                if (!token->isOperator()) break;

                auto operFromStack = dynamic_cast<Operator *>(operatorStack.peek());
                if (oper->getPrecedence() > operFromStack->getPrecedence()) break;

                auto expr2 = expressionStack.pop();
                auto expr1 = expressionStack.pop();
                expressionStack.push(new OperatorNode(operFromStack, expr1, expr2));
            }
            operatorStack.push(oper);
        } else if (c == '(') {
            operatorStack.push(OpeningBracket::getInstance());
        } else if (c == ')') {
            while (!operatorStack.empty()) {
                auto token = operatorStack.pop();
                if (token->isOperator()) {
                    auto expr2 = expressionStack.pop();
                    auto expr1 = expressionStack.pop();
                    expressionStack.push(new OperatorNode(dynamic_cast<Operator *>(token), expr1, expr2));
                } else break;
            }
        } else {
            int start = i++;
            for (; i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'); ++i) {}

            double number = stod(expression.substr(start, i - start));
            auto token = new Number(number);
            expressionStack.push(new ConstantNode(token));
            i--;
        }
    }

    while (!operatorStack.empty()) {
         auto expr2 = expressionStack.pop();
         auto expr1 = expressionStack.pop();
         auto token = operatorStack.pop();
         expressionStack.push(new OperatorNode(dynamic_cast<Operator *>(token), expr1, expr2));
    }

    auto output = expressionStack.pop(); // there must be only 1 element by now
    if (!expressionStack.empty()) {
        throw logic_error("Expression stack is not empty");
    }

    return output;
}

bool shouldParseAsOperator(const string &expression, int position) {
    char c = expression[position];
    if (c != '-' && c != '+') {
        return Operator::isOperator(c);
    }

    char previous = NOT_FOUND;
    for (int i = position - 1; i >= 0; i--) {
        if (!isspace(expression[i])) {
            previous = expression[i];
            break;
        }
    }

    return previous != NOT_FOUND && previous != '(';
}
