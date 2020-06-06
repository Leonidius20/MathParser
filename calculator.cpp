#include <vector>
#include "token.h"
#include "stack.h"
#include "calculator.h"
#include <stdexcept>

using namespace std;

double compute(const vector<Token *> &tokens) {
    Stack<double> numbers;
    for (auto token : tokens) {
        if (!token->isOperator()) {
            auto numberToken = dynamic_cast<Number *>(token);
            numbers.push(numberToken->getValue());
        } else {
            auto operatorToken = dynamic_cast<Operator *>(token);
            double operand2 = numbers.pop(), operand1 = numbers.pop();
            double value = operatorToken->apply(operand1, operand2);
            numbers.push(value);
        }
    }
    if (numbers.empty()) {
        throw invalid_argument("compute(): ill-formed input");
    }
    return numbers.pop();
}