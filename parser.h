#pragma once

#include <string>
#include <utility>
#include <vector>
#include "TreeNode.h"
#include "token.h"

/* Grammar:

statement_list: empty | (statement)*

statement_block: LCURLY statementList RCURLY

statement: (expression | assignment | branch | empty);

expression: term ((PLUS | MINUS) term)*

term: factor ((MUL|DIV) factor)*

factor: value (^ value)*

value: PLUS value | MINUS value | NUMBER | LPAREN expression RPAREN | variable

variable: ID

assignment: variable ASSIGN expression

branch: IF LPAREN expression RPAREN statement_block (ELSE statement_block)


*/

class Parser {
    std::vector<Token *> tokens;
    unsigned offset = 0;

    void eatToken(TokenType type);

    StatementListNode *parseStatementList();

    TreeNode *parseStatement();

    ExpressionNode *parseExpression();

    AssignmentNode *parseAssignment();

    VariableNode *parseVariable();

    BranchNode *parseBranch();

    StatementListNode *parseStatementBlock();

    ExpressionNode *parseTerm();
public:
    explicit Parser(std::vector<Token *> tokens) : tokens(std::move(tokens)) {}

    StatementListNode *parse();
};

StatementListNode *parseCode(const std::string &code);