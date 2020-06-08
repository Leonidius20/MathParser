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
        throw invalid_argument("Unknown operator: " + string(1, signature));
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

map<char, Token *> *Token::tokenMap = new map<char, Token *>{
        {'=', Assignment::getInstance()},
        {';', Semicolon::getInstance()},
        {'(', OpeningBracket::getInstance()},
        {')', ClosingBracket::getInstance()},
        {'{', OpeningCurlyBracket::getInstance()},
        {'}', ClosingCurlyBracket::getInstance()},
};

Token *Token::get(char symbol) {
    if (!isNonOperatorToken(symbol)) {
        throw invalid_argument("Unknown token: " + string(1, symbol));
    }

    return tokenMap->at(symbol);
}

