#include <string>
#include <stdexcept>
#include "parser.h"

using namespace std;

StatementListNode *Parser::parse() {
    return parseStatementList();
}

void Parser::eatToken(TokenType type) {
    if (tokens[offset]->getType() != type) {
        string what = "Syntax error at offset ";
        what.append(to_string(offset));
        what.append(": unexpected token, expected token #");
        what.append(to_string(type));
        throw invalid_argument(what);
    } else offset++;
}

/*
 * empty | (statement)*
 */
StatementListNode *Parser::parseStatementList() {
    auto node = new StatementListNode;
    while (offset < tokens.size() && tokens[offset] != ClosingCurlyBracket::getInstance()) {
        node->statements.push_back(parseStatement());
    }
    return node;
}

/*
 * LCURLY statementList RCURLY
 */
StatementListNode *Parser::parseStatementBlock() {
    eatToken(TokenType::OPENING_CURLY_BRACKET);
    auto body = parseStatementList();
    eatToken(TokenType::CLOSING_CURLY_BRACKET);
    return body;
}

/*
 * (expression | assignment | branch | empty)
 */
TreeNode *Parser::parseStatement() {
    if (tokens[offset]->getType() == TokenType::IDENTIFIER
        && tokens[offset + 1]->getType() == TokenType::ASSIGNMENT) {
        return parseAssignment();
    } else if (tokens[offset]->getType() == TokenType::IF_TOKEN) {
        return parseBranch();
    } else {
        return parseExpression();
    }
}

/*
 * variable ASSIGN expression
 */
AssignmentNode *Parser::parseAssignment() {
    auto variable = parseVariable();
    eatToken(TokenType::ASSIGNMENT);
    auto value = parseExpression();
    return new AssignmentNode(variable, value);
}

/*
 * ID
 */
VariableNode *Parser::parseVariable() {
    string name = dynamic_cast<Identifier *>(tokens[offset])->getName();
    offset++;
    return new VariableNode(name);
}

/*
 * IF LPAREN expression RPAREN statement_block (ELSE statement_block)
 */
BranchNode *Parser::parseBranch() {
    eatToken(TokenType::IF_TOKEN);
    eatToken(TokenType::OPENING_BRACKET);
    auto condition = parseExpression();
    eatToken(TokenType::CLOSING_BRACKET);
    auto ifTrue = parseStatementBlock();
    StatementListNode *ifFalse = nullptr;
    if (tokens[offset]->getType() == TokenType::ELSE_TOKEN) {
        eatToken(ELSE_TOKEN);
        ifFalse = parseStatementBlock();
    }
    return new BranchNode(condition, ifTrue, ifFalse);
}

ExpressionNode *Parser::parseTerm() {
    return nullptr;
}


ExpressionNode *Parser::parseExpression() {
    ExpressionNode *term1 = parseTerm();
    // TODO: keep track of opened and closed brackets, stop when you see extra closing bracket (if condition)
    //while (text[offset])

    return nullptr;
}













