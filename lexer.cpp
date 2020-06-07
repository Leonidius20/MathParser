#include <vector>
#include <string>
#include "token.h"
#include "lexer.h"

using namespace std;

Token *Lexer::readIdentifier() {
    string name;

    char c = text[offset];
    offset--; // TODO: remake the shitcode

    while (++offset != text.size() && isalnum(c = text[offset])) {
        name.append(string(1, c));
    }

    if (name == "if") return IfToken::getInstance();
    else if (name == "else") return ElseToken::getInstance();
    else return new Identifier(name);
}

Token *Lexer::readNumber() {
    string number;

    char c = text[offset];
    offset--;

    while (++offset != text.size() && (isdigit(c = text[offset]) || (c = text[offset]) == '.')) {
        number.append(string(1, c));
    }

    return new Number(stod(number));
}

vector<Token *> Lexer::tokenize() {
    vector<Token *> output;

    for (offset = 0; offset < text.size(); offset++) {
        char c = text[offset];

        if (isspace(c)) continue;

        else if (isalpha(c)) {
            output.push_back(readIdentifier());
        } else if (isdigit(c)) {
            output.push_back(readNumber());
        } else if (c == '=') {
            output.push_back(Assignment::getInstance());
        } else if (c == ';') {
            output.push_back(Semicolon::getInstance());
        } else if (c == '(') {
            output.push_back(OpeningBracket::getInstance());
        } else if (c == ')') {
            output.push_back(ClosingBracket::getInstance());
        } else if (c == '{') {
            output.push_back(OpeningCurlyBracket::getInstance());
        } else if (c == '}') {
            output.push_back(ClosingCurlyBracket::getInstance());
        } else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^') {
            output.push_back(Operator::get(c));
            // TODO: fix ^ operator not adding
        }
    }

    return output;
}