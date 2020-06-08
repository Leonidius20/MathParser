#pragma once

#include <utility>
#include <vector>
#include <string>
#include "token.h"

class Lexer {
    std::string text;
    unsigned offset = 0;

    Token *readIdentifier();

    Token *readNumber();
public:
    explicit Lexer(std::string input) : text(std::move(input)) {}
    std::vector<Token *> tokenize();
};

