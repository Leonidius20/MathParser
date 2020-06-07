#pragma once

#include <vector>
#include <string>
#include "token.h"

class Lexer {
    std::string text;
    unsigned offset;

    Token *readIdentifier();

    Token *readNumber();
public:
    Lexer(const std::string &input) : text(input) {}
    std::vector<Token *> tokenize();
};

