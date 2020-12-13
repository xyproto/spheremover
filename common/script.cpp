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

#include "script.hpp"

using namespace std::string_literals;

auto tokenize(const std::string source) -> std::vector<Token>
{
    std::string kw = ""s; // a keyword
    std::string digits = ""s; // a number
    std::string op = ""s; // an operator
    std::string str = ""s; // a string literal
    bool inString = false;
    std::vector<Token> tokens;
    for (auto r : source) {
        // First, gather strings, keywords, numbers and names
        if (!inString && r == '"') {
            // Start collecting letters between " and "
            inString = true;
            continue;
        } else if (inString && r != '"') {
            // Collect another letter of the string
            str += std::string(1, r);
            continue;
        } else if (inString && r == '"') {
            // No longer collecting, push a string token
            tokens.push_back(Token { TokenType::STRING, str });
            str = ""s;
            inString = false;
            continue;
        } else if ((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z')) {
            // Collect keyword letters
            kw += std::string(1, r);
            continue;
        } else if (r >= '0' && r <= '9') {
            // Collect number digits
            digits += std::string(1, r);
            continue;
        } else if (r == '>' || r == '<' || r == '=') {
            // Collect operators longer than 1 rune
            op += std::string(1, r);
            continue;
        } else {
            // If no longer gathering, push non-empty keywords and numbers, then go on
            if (!kw.empty()) {
                // TODO: Loop over a list of keywords that can be recognized
                if (kw == "if") {
                    tokens.push_back(Token { TokenType::KEYWORD, kw });
                } else if (kw == "for") {
                    tokens.push_back(Token { TokenType::KEYWORD, kw });
                } else {
                    // not a recognized keyword, assume it's a name/literal
                    tokens.push_back(Token { TokenType::NAME, kw });
                }
                // then reset the kw string
                kw = ""s;
            } else if (!digits.empty()) {
                tokens.push_back(Token { TokenType::NUMBER, digits });
                // then reset the digits string
                digits = ""s;
            } else if (!op.empty()) {
                if (op == "<") {
                    tokens.push_back(Token { TokenType::LT, "<" });
                } else if (op == ">") {
                    tokens.push_back(Token { TokenType::GT, ">" });
                } else if (op == "<=") {
                    tokens.push_back(Token { TokenType::LTEQ, "<=" });
                } else if (op == ">=") {
                    tokens.push_back(Token { TokenType::GTEQ, ">=" });
                } else if (op == "==") {
                    tokens.push_back(Token { TokenType::EQ, "==" });
                }
                // then reset the operator string
                op = ""s;
            }
        }
        // Then handle the other characters that aren't collectable strings
        switch (r) {
        case ';':
            tokens.push_back(Token { TokenType::SEMICOLON, ";" });
            break;
        case '(':
            tokens.push_back(Token { TokenType::PAROPEN, "(" });
            break;
        case ')':
            tokens.push_back(Token { TokenType::PARCLOSE, ")" });
            break;
        case '{':
            tokens.push_back(Token { TokenType::BLOCKOPEN, "{" });
            break;
        case '}':
            tokens.push_back(Token { TokenType::BLOCKCLOSE, "}" });
            break;
        case ' ':
        case '\t':
        case '\n':
            // Ignore whitespace and newlines
            break;
        default:
            // Unrecognized runes
            tokens.push_back(Token { TokenType::UNRECOGNIZED, std::string(1, r) });
            std::cout << "UNRECOGNIZED LETTER: "s << r << std::endl;
            break;
        }
    }

    // Final token push, for gathered keywords and numbers
    if (!kw.empty()) {
        tokens.push_back(Token { TokenType::KEYWORD, kw });
    } else if (!digits.empty()) {
        tokens.push_back(Token { TokenType::NUMBER, digits });
    }

    // Return all tokens
    return tokens;
}

auto interpret(std::vector<Token> tokens) -> int
{
    for (auto tok : tokens) {
        std::cout << "TOKEN "s << tok.source << " ("s << tok.type << ")"s << std::endl;
    }
    // success
    return 0;
}
