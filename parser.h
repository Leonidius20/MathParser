#pragma once

#include <string>
#include <vector>
#include "TreeNode.h"
#include "token.h"

class Parser {
    std::vector<Token *> tokens;
    unsigned offset;

    StatementListNode *parseStatementList();

    TreeNode *parseStatement();
public:
    Parser(const std::vector<Token *> &tokens) : tokens(tokens) {}

    StatementListNode *parse();
};

StatementListNode *parseCode(const std::string &code);