#pragma once

#include <string>
#include <map>
#include <utility>

class Token {
    static std::map<char, Token *> *tokenMap;

public:

    enum Type {
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

    [[nodiscard]] virtual Type getType() const = 0;

    static Token *get(char symbol);

    static bool isNonOperatorToken(char symbol) { return tokenMap->contains(symbol); }

    static void destroyMap() { delete tokenMap; };

    virtual ~Token() = default;
};

class Number : public Token {
    const double value;

public:

    explicit Number(double value) : value(value) {}

    [[nodiscard]] double getValue() const { return value; };

    [[nodiscard]] Type getType() const override { return Type::NUMBER; };

    ~Number() override = default;
};

class Operator : public Token {
    const int precedence;
    const char signature;
    static std::map<char, Operator> *operatorMap;

public:

    Operator(const int precedence, char signature) : precedence(precedence), signature(signature) {}

    static Operator *get(char signature);

    static bool isOperator(char signature) { return operatorMap->contains(signature); }

    [[nodiscard]] int getPrecedence() const { return precedence; }

    [[nodiscard]] char getSignature() const { return signature; }

    [[nodiscard]] double apply(double a, double b) const;

    [[nodiscard]] Type getType() const override { return Type::OPERATOR; };

    static void destroyMap() { delete operatorMap; }

    ~Operator() override = default;
};

class OpeningBracket : public Token {
    static OpeningBracket *instance;

    OpeningBracket() = default;

public:

    static OpeningBracket *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::OPENING_BRACKET; };
};

class ClosingBracket : public Token {
    static ClosingBracket *instance;

public:

    static ClosingBracket *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::CLOSING_BRACKET; };
};

class Identifier : public Token {
    std::string name;

public:

    explicit Identifier(std::string name) : name(std::move(name)) {};

    [[nodiscard]] std::string getName() const { return name; };

    [[nodiscard]] Type getType() const override { return Type::IDENTIFIER; };
};

class Assignment : public Token {
    static Assignment *instance;

public:

    static Assignment *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::ASSIGNMENT; };
};

class IfToken : public Token {
    static IfToken *instance;

public:

    static IfToken *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::IF_TOKEN; };
};

class ElseToken : public Token {
    static ElseToken *instance;

public:

    static ElseToken *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::ELSE_TOKEN; };
};

class OpeningCurlyBracket : public Token {
    static OpeningCurlyBracket *instance;

public:

    static OpeningCurlyBracket *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::OPENING_CURLY_BRACKET; };
};

class ClosingCurlyBracket : public Token {
    static ClosingCurlyBracket *instance;

public:

    static ClosingCurlyBracket *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::CLOSING_CURLY_BRACKET; };
};

class Semicolon : public Token {
    static Semicolon *instance;

public:

    static Semicolon *getInstance() { return instance; };

    [[nodiscard]] Type getType() const override { return Type::SEMICOLON; };
};