#include <vector>
#include <string>
#include <stdexcept>
#include "token.h"
#include "lexer.h"

using namespace std;

Token *Lexer::readIdentifier() {
    string name;

    char c = text[offset];
    name.append(string(1, c));

    while (offset + 1 != text.size() && isalnum(text[offset + 1])) {
        offset++;
        c = text[offset];
        name.append(string(1, c));
    }

    if (name == "if") return IfToken::getInstance();
    else if (name == "else") return ElseToken::getInstance();
    else return new Identifier(name);
}

Token *Lexer::readNumber() {
    string number;

    char c = text[offset];
    number.append(string(1, c));

    while (offset + 1 != text.size() && (isdigit(text[offset + 1]) || text[offset + 1] == '.')) {
        offset++;
        c = text[offset];
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
        } else if (Operator::isOperator(c)) {
            output.push_back(Operator::get(c));
        } else if (Token::isNonOperatorToken(c)) {
            output.push_back(Token::get(c));
        } else {
            throw invalid_argument("Unrecognized symbol during tokenizing");
        }
    }

    return output;
}