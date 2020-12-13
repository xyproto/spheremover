#pragma once

/*
 * Okay, I need a function that can tokenize a string.
 * Then I need a function that can match tokens with expressions etc.
 * Then I need a function that can handle an "if".
 * Then I need a function that can handle a function call.
 * Also a connection to C++ is needed.
 * The ability to create a class in C++ is needed.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std::string_literals;

enum class TokenType {
    SEMICOLON,
    PAROPEN,
    PARCLOSE,
    BLOCKOPEN,
    BLOCKCLOSE,
    GT, // greater than
    LT, // less than
    GTEQ, // greater than or equal to
    LTEQ, // less than or equal to
    EQ, // equal to
    KEYWORD, // a recognized keyword, like "if"
    NAME, // a non-recognized keyword, like "x"
    NUMBER,
    STRING,
    NEWLINE,
    UNRECOGNIZED
};

class Token {
public:
    TokenType type;
    std::string source;
};

auto tokenize(const std::string source) -> std::vector<Token>;

auto interpret(std::vector<Token> tokens) -> int;

inline std::ostream& operator<<(std::ostream& os, const TokenType& type)
{
    switch (type) {
    case TokenType::SEMICOLON:
        os << "semicolon";
        break;
    case TokenType::PAROPEN:
        os << "paropen";
        break;
    case TokenType::PARCLOSE:
        os << "parclose";
        break;
    case TokenType::BLOCKOPEN:
        os << "blockopen";
        break;
    case TokenType::BLOCKCLOSE:
        os << "blockclose";
        break;
    case TokenType::NEWLINE:
        os << "newline";
        break;
    case TokenType::KEYWORD:
        os << "keyword";
        break;
    case TokenType::NAME: // identifier
        os << "name";
        break;
    case TokenType::NUMBER:
        os << "number";
        break;
    case TokenType::STRING:
        os << "string";
        break;
    case TokenType::EQ:
        os << "eq";
        break;
    case TokenType::GT:
        os << "gt";
        break;
    case TokenType::LT:
        os << "lt";
        break;
    case TokenType::GTEQ:
        os << "gteq";
        break;
    case TokenType::LTEQ:
        os << "lteq";
        break;
    case TokenType::UNRECOGNIZED:
        os << "unrecognized";
        break;
    default:
        os << "invalid";
        break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Token& tok)
{
    os << "Token \""s << tok.source << "\" ("s << tok.type << ")"s;
    return os;
}
