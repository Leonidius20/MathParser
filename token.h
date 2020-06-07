#pragma once

#include <string>
#include <map>
#include <utility>

enum TokenType {
    NUMBER,                  // 0
    IDENTIFIER,              // 1
    OPERATOR,                // 2
    OPENING_BRACKET,         // 3
    CLOSING_BRACKET,         // 4
    ASSIGNMENT,              // 5
    OPENING_CURLY_BRACKET,   // 6
    CLOSING_CURLY_BRACKET,   // 7
    SEMICOLON,               // 8
    IF_TOKEN,                // 9
    ELSE_TOKEN,              // 10
};

class Token {
public:
    [[nodiscard]] virtual TokenType getType() const = 0;
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

    [[nodiscard]] TokenType getType() const override { return TokenType::NUMBER; };

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

    [[nodiscard]] double apply(double a, double b) const;

    [[nodiscard]] TokenType getType() const override { return TokenType::OPERATOR; };

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

    [[nodiscard]] TokenType getType() const override { return TokenType::OPENING_BRACKET; };
};

class ClosingBracket : public Token {
    static ClosingBracket *instance;
public:
    static ClosingBracket *getInstance() { return instance; };

    [[nodiscard]] TokenType getType() const override { return TokenType::CLOSING_BRACKET; };
};

class Identifier : public Token {
    std::string name;
public:
    explicit Identifier(std::string name) : name(std::move(name)) {};

    [[nodiscard]] std::string getName() const { return name; };

    [[nodiscard]] TokenType getType() const override { return TokenType::IDENTIFIER; };
};

class Assignment : public Token {
    static Assignment *instance;
public:
    static Assignment *getInstance() { return instance; };

    [[nodiscard]] TokenType getType() const override { return TokenType::ASSIGNMENT; };
};

class IfToken : public Token {
    static IfToken *instance;
public:
    static IfToken *getInstance() { return instance; };

    [[nodiscard]] TokenType getType() const override { return TokenType::IF_TOKEN; };
};

class ElseToken : public Token {
    static ElseToken *instance;
public:
    static ElseToken *getInstance() { return instance; };

    [[nodiscard]] TokenType getType() const override { return TokenType::ELSE_TOKEN; };
};

class OpeningCurlyBracket : public Token {
    static OpeningCurlyBracket *instance;
public:
    static OpeningCurlyBracket *getInstance() { return instance; };

    [[nodiscard]] TokenType getType() const override { return TokenType::OPENING_CURLY_BRACKET; };
};

class ClosingCurlyBracket : public Token {
    static ClosingCurlyBracket *instance;
public:
    static ClosingCurlyBracket *getInstance() { return instance; };

    [[nodiscard]] TokenType getType() const override { return TokenType::CLOSING_CURLY_BRACKET; };
};

class Semicolon : public Token {
    static Semicolon *instance;
public:
    static Semicolon *getInstance() { return instance; };

    [[nodiscard]] TokenType getType() const override { return TokenType::SEMICOLON; };
};