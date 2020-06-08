#include <string>
#include <stdexcept>
#include "token.h"
#include "parser.h"

using namespace std;

using TokenType = Token::TokenType;

Tree Parser::parse() {
    return Tree(parseStatementList());
}

void Parser::eatToken(TokenType type) {
    if (offset >= tokens.size()) {
        string what = "Syntax error at offset ";
        what.append(to_string(offset));
        what.append(": unexpected end of file, expected token #");
        what.append(to_string(type));
        throw invalid_argument(what);
    }
    if (tokens[offset]->getType() != type) {
        string what = "Syntax error at offset ";
        what.append(to_string(offset));
        what.append(": unexpected token, expected token #");
        what.append(to_string(type));
        throw invalid_argument(what);
    } else offset++;
}

Operator *Parser::eatOperator(int precedence) {
    if (offset >= tokens.size()) {
        string what = "Syntax error at offset ";
        what.append(to_string(offset));
        what.append(": unexpected end of file, expected token #");
        what.append(to_string(TokenType::OPERATOR));
        throw invalid_argument(what);
    }

    if (tokens[offset]->getType() != TokenType::OPERATOR) {
        string what = "Syntax error at offset ";
        what.append(to_string(offset));
        what.append(": unexpected token, expected token #");
        what.append(to_string(TokenType::OPERATOR));
        throw invalid_argument(what);
    }

    auto op = dynamic_cast<Operator *>(tokens[offset]);
    if (op->getPrecedence() != precedence) {
        string what = "Syntax error at offset ";
        what.append(to_string(offset));
        what.append(": unexpected operator, expected operator with precedence ");
        what.append(to_string(precedence));
        throw invalid_argument(what);
    }

    offset++;

    return op;
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
 * (expression | assignment | branch | empty);
 */
TreeNode *Parser::parseStatement() {
    if (offset < tokens.size() && tokens[offset]->getType() == TokenType::IDENTIFIER
        && tokens[offset + 1]->getType() == TokenType::ASSIGNMENT) {
        auto assignment = parseAssignment();
        eatToken(TokenType::SEMICOLON);
        return assignment;
    } else if (offset < tokens.size() && tokens[offset]->getType() == TokenType::IF_TOKEN) {
        return parseBranch();
    } else {
        auto expr = parseExpression();
        eatToken(TokenType::SEMICOLON);
        return expr;
    }
}

/*
 * term ((PLUS | MINUS) term)*
 */
ExpressionNode *Parser::parseExpression() {
    ExpressionNode *node = parseTerm();

    while (offset < tokens.size() && tokens[offset]->getType() == TokenType::OPERATOR) {
        auto op = dynamic_cast<Operator *>(tokens[offset]);
        if (op->getPrecedence() != 1) break;
        offset++;
        auto term = parseTerm();
        node = new OperatorNode(op, node, term);
    }

    return node;
}

/*
 * factor ((MUL|DIV) factor)*
 */
ExpressionNode *Parser::parseTerm() {
    ExpressionNode *node = parseFactor();

    while (offset < tokens.size() && tokens[offset]->getType() == TokenType::OPERATOR) {
        auto op = dynamic_cast<Operator *>(tokens[offset]);
        if (op->getPrecedence() != 2) break;
        offset++;
        auto term = parseFactor();
        node = new OperatorNode(op, node, term);
    }

    return node;
}

/*
 * value (^ value)*
 */
ExpressionNode *Parser::parseFactor() {
    ExpressionNode *node = parseValue();

    while (offset < tokens.size() && tokens[offset]->getType() == TokenType::OPERATOR) {
        auto op = dynamic_cast<Operator *>(tokens[offset]);
        if (op->getPrecedence() != 3) break;
        offset++;
        auto term = parseValue();
        node = new OperatorNode(op, node, term);
    }

    return node;
}

/*
 * PLUS value | MINUS value | NUMBER | LPAREN expression RPAREN | variable
 */
ExpressionNode *Parser::parseValue() {
    switch (tokens[offset]->getType()) {
        case TokenType::OPERATOR: { // unary operator
            auto op = eatOperator(1);
            auto value = parseValue();
            return new OperatorNode(op, new ConstantNode(new Number(0)), value);
        }
        case TokenType::NUMBER: {
            auto token = dynamic_cast<Number *>(tokens[offset]);
            eatToken(TokenType::NUMBER);
            return new ConstantNode(token);
        }
        case TokenType::OPENING_BRACKET: {
            eatToken(TokenType::OPENING_BRACKET);
            auto expression = parseExpression();
            eatToken(TokenType::CLOSING_BRACKET);
            return expression;
        }
        case TokenType::IDENTIFIER: {
            return parseVariable();
        }
        default: {
            string what = "Syntax error at offset ";
            what.append(to_string(offset));
            what.append(": unexpected token, expected tokens #");
            what.append(to_string(TokenType::OPERATOR));
            what.append(", ").append(to_string(TokenType::OPENING_BRACKET));
            what.append(" or ").append(to_string(TokenType::IDENTIFIER));
            throw invalid_argument(what);
        }
    }
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
 * variable ASSIGN expression
 */
AssignmentNode *Parser::parseAssignment() {
    auto variable = parseVariable();
    eatToken(TokenType::ASSIGNMENT);
    auto value = parseExpression();
    return new AssignmentNode(variable, value);
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
    if (offset < tokens.size() && tokens[offset]->getType() == TokenType::ELSE_TOKEN) {
        eatToken(TokenType::ELSE_TOKEN);
        ifFalse = parseStatementBlock();
    }
    return new BranchNode(condition, ifTrue, ifFalse);
}