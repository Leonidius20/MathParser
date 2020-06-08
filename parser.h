#pragma once

#include <string>
#include <utility>
#include <vector>
#include "Tree.h"
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

    void eatToken(Token::Type type);

    Operator *eatOperator(int precedence);

    StatementListNode *parseStatementList();

    StatementListNode *parseStatementBlock();

    TreeNode *parseStatement();

    ExpressionNode *parseExpression();

    ExpressionNode *parseTerm();

    ExpressionNode *parseFactor();

    ExpressionNode *parseValue();

    VariableNode *parseVariable();

    AssignmentNode *parseAssignment();

    BranchNode *parseBranch();

public:
    explicit Parser(std::vector<Token *> tokens) : tokens(std::move(tokens)) {}

    Tree parse();
};