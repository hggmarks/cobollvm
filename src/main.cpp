#include <iostream>
#include <string>
#include "lexer.hpp"


std::string tokenTypeToString(TokenType type) {
  switch (type) {
    case TokenType::IDENTIFICATION: return "IDENTIFICATION";
    case TokenType::PROGRAM_ID: return "PROGRAM_ID";
    case TokenType::DATA: return "DATA";
    case TokenType::PROCEDURE: return "PROCEDURE";
    case TokenType::IDENTIFIER: return "IDENTIFIER";
    case TokenType::NUMBER: return "NUMBER";
    case TokenType::PERIOD: return "PERIOD";
    case TokenType::END_OF_FILE: return "EOF";
    case TokenType::INVALID: return "INVALID";
    default: return "UNKNOWN";
  }
}


int main() {
  
  std::string input = R"(
    IDENTIFICATION DIVISION.
    PROGRAM_ID. HELLO.
    DATA DIVISION.
    PROCEDURE DIVISION.
  )";

  Lexer lexer(input);

  while (true) {

    Token token = lexer.nextToken();

    std::cout << "Token: " << tokenTypeToString(token.type)
      << " | Lexeme: '" << token.lexeme
      << "' | Line: " << token.line
      << " | Column: " << token.column << std::endl;

    if (token.type == TokenType::END_OF_FILE) break;
  }

  return 0;
}
