#pragma once

#include <string>
#include <map>

class Token {
public:
    virtual bool isOperator() = 0;
    virtual bool isNumber() = 0;
    virtual ~Token() = default;
};

class Number : public Token {
private:
    const double value;
public:
    explicit Number(double value) : value(value) {}

    [[nodiscard]] double getValue() const { return value; };

    bool isOperator() override { return false; };

    bool isNumber() override { return true; };

    ~Number() override = default;
};

class Operator : public Token {
private:
    const int precedence;
    const char signature;
    static std::map<char, Operator> *operatorMap;

    Operator(const int precedence, char signature) : precedence(precedence), signature(signature) {}

public:

    static Operator *get(char signature);

    static bool isOperator(char signature) { return operatorMap->contains(signature); }

    bool isOperator() override { return true; };

    bool isNumber() override { return false; };

    [[nodiscard]] int getPrecedence() const { return precedence; }

    double apply(double a, double b);

    static void destroyMap() { delete operatorMap; }

    ~Operator() override = default;
};

class OpeningBracket : public Token {
private:
    static OpeningBracket *instance;

    OpeningBracket() = default;

public:

    bool isOperator() override { return false; };

    bool isNumber() override { return false; };

    static OpeningBracket *getInstance() { return instance; };
};
