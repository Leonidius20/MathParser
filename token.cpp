#include "token.h"
#include <cmath>
#include <stdexcept>

using namespace std;

double Operator::apply(double a, double b) const {
    if (signature == '+') {
        return a + b;
    } else if (signature == '-') {
        return a - b;
    } else if (signature == '*') {
        return a * b;
    } else if (signature == '/') {
        return a / b;
    } else if (signature == '^') {
        return pow(a, b);
    } else {
        throw invalid_argument("Unknown operator: " + to_string(signature));
    }
}

map<char, Operator> *Operator::operatorMap = new map<char, Operator>{
        {'+', Operator(1, '+')},
        {'-', Operator(1, '-')},
        {'*', Operator(2, '*')},
        {'/', Operator(2, '/')},
        {'^', Operator(3, '^')},
};

Operator *Operator::get(char signature) {
    if (!isOperator(signature)) {
        throw invalid_argument("Unknown operator: " + to_string(signature));
    }
    return &operatorMap->at(signature);
}

OpeningBracket *OpeningBracket::instance = new OpeningBracket();
ClosingBracket *ClosingBracket::instance = new ClosingBracket();
Assignment *Assignment::instance = new Assignment();
IfToken *IfToken::instance = new IfToken();
ElseToken *ElseToken::instance = new ElseToken();
OpeningCurlyBracket *OpeningCurlyBracket::instance = new OpeningCurlyBracket();
ClosingCurlyBracket *ClosingCurlyBracket::instance = new ClosingCurlyBracket();
Semicolon *Semicolon::instance = new Semicolon();