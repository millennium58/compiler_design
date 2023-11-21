#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

// Token types
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    LITERAL,
    // ... other types
};

// Token names
std::map<TokenType, std::string> tokenNames = {
    {KEYWORD, "Keyword"},
    {IDENTIFIER, "Identifier"},
    {OPERATOR, "Operator"},
    {LITERAL, "Literal"}
    // Add more mappings as needed
};

// Mapping of token types to regular expressions
std::map<TokenType, std::string> tokenRegexes = {
    {KEYWORD, "(int|float|if|else|while|for)"},
    {IDENTIFIER, "[a-zA-Z_][a-zA-Z0-9_]*"},
    {OPERATOR, "[+\\-*/]"},
    {LITERAL, "[0-9]+"}
    // Add more mappings as needed
};

// Token structure
struct Token {
    TokenType type;
    std::string name;
    std::string attribute;
    std::string lexeme;
};

// Tokenize input code
std::vector<Token> tokenize(const std::string &input) {
    std::vector<Token> tokens;

    for (const auto &pair : tokenRegexes) {
        TokenType type = pair.first;
        const std::string &regexPattern = pair.second;

        std::regex pattern(regexPattern);
        std::sregex_iterator iter(input.begin(), input.end(), pattern);
        std::sregex_iterator end;

        while (iter != end) {
            Token token;
            token.type = type;
            token.name = tokenNames[type];
            token.attribute = "Attribute"; // Add actual attributes if needed
            token.lexeme = iter->str();
            tokens.push_back(token);
            ++iter;
        }
    }

    return tokens;
}

int main() {
    std::string cppCode;
    std::cout << "Enter C++ code:" << std::endl;
    std::getline(std::cin, cppCode);

    // Tokenize the code
    std::vector<Token> tokens = tokenize(cppCode);

    // Display tokens
    std::cout << "Tokens:" << std::endl;
    for (const Token &token : tokens) {
        std::cout << "Type: " << token.name << " | Attribute: " << token.attribute
                  << " | Lexeme: " << token.lexeme << std::endl;
    }

    return 0;
}
