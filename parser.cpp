#include <string>
#include "parser.h"

using namespace std;

TreeNode *Parser::parseStatement() {

}

StatementListNode *Parser::parseStatementList() {
    StatementListNode node;
    while (tokens[offset] != Semicolon::getInstance()) {
        node.statements.push_back(parseStatement());
    }

    return nullptr;
}

StatementListNode *Parser::parse() {
    return parseStatementList();
}