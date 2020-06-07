#pragma once

#include <string>
#include <map>

class Token {

};

class MathToken : public Token {
public:
    virtual bool isOperator() = 0;

    virtual bool isNumber() = 0;

    virtual ~MathToken() = default;
};

class Number : public MathToken {
    const double value;
public:
    explicit Number(double value) : value(value) {}

    [[nodiscard]] double getValue() const { return value; };

    bool isOperator() override { return false; };

    bool isNumber() override { return true; };

    ~Number() override = default;
};

class Operator : public MathToken {
    const int precedence;
    const char signature;
    static std::map<char, Operator> *operatorMap;

public:
    Operator(const int precedence, char signature) : precedence(precedence), signature(signature) {}

    static Operator *get(char signature);

    static bool isOperator(char signature) { return operatorMap->contains(signature); }

    bool isOperator() override { return true; };

    bool isNumber() override { return false; };

    [[nodiscard]] int getPrecedence() const { return precedence; }

    double apply(double a, double b);

    static void destroyMap() { delete operatorMap; }

    ~Operator() override = default;
};

class OpeningBracket : public MathToken {
    static OpeningBracket *instance;

    OpeningBracket() = default;

public:

    bool isOperator() override { return false; };

    bool isNumber() override { return false; };

    static OpeningBracket *getInstance() { return instance; };
};

class ClosingBracket : public Token {
    static ClosingBracket *instance;
public:
    static ClosingBracket *getInstance() { return instance; };
};

class Identifier : public Token {
    std::string name;
public:
    Identifier(const std::string &name) : name(name) {};

    [[nodiscard]] std::string getName() const { return name; };
};

class Assignment : public Token {
    static Assignment *instance;
public:
    static Assignment *getInstance() { return instance; };
};

class IfToken : public Token {
    static IfToken *instance;
public:
    static IfToken *getInstance() { return instance; };
};

class OpeningCurlyBracket : public Token {
    static OpeningCurlyBracket *instance;
public:
    static OpeningCurlyBracket *getInstance() { return instance; };
};

class ClosingCurlyBracket : public Token {
    static ClosingCurlyBracket *instance;
public:
    static ClosingCurlyBracket *getInstance() { return instance; };
};

class Semicolon : public Token {
    static Semicolon *instance;
public:
    static Semicolon *getInstance() { return instance; };
};