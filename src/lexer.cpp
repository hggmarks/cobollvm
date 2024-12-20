#include "lexer.hpp"
#include <cctype>
#include <unordered_map>


static const std::unordered_map<std::string, TokenType> keywords = {
  {"IDENTIFICATION", TokenType::IDENTIFICATION},
  {"PROGRAM_ID", TokenType::PROGRAM_ID},
  {"DATA", TokenType::DATA},
  {"PROCEDURE", TokenType::PROCEDURE}
};

Lexer::Lexer(std::string input) : source(std::move(input)) {}

char Lexer::advance() {
  if (isValidPosition()) {
    char current = source[++pos];
    column++;
    if (current == '\n') {
      line++;
      column = 1;
    }
    return current;
  }
  return '\0'; 
}


char Lexer::peek() const {
  if (isValidPosition()) {
    return source[pos + 1];
  }

  return '\0';
}

void Lexer::skipWhitespace() {
  while (isValidPosition() && std::isspace(peek())) {
    advance();
  }
}

bool Lexer::isAtEnd() const {
  return pos >= source.length();
}

Token Lexer::alphanumLiteral(char strDelimiter) {
    std::string literalContent;
    literalContent += advance();
    int startColumn = column;

    char curr = advance();
    while (curr != strDelimiter || (curr == strDelimiter && peek() == strDelimiter)) {

      if (curr == '\r' || curr == '\n') {
        return Token(TokenType::INVALID, std::string(1, curr), line, column);
      }


      if (curr == strDelimiter && peek() == strDelimiter) {
        advance();
        literalContent += strDelimiter;
      } else {
        literalContent += curr;
      }

     curr = advance();
    }

    literalContent += curr;

    return Token(TokenType::STANDARD_ALPHANUM, literalContent, line, startColumn);

}

Token Lexer::identifier() {
  int startColumn = column;
    std::string result;
    
    // First, add the current character
    //skipWhitespace();
    
    // Then continue with the rest of the identifier
    while (isValidPosition() && (std::isalnum(peek()) || peek() == '-')) {
        result += advance();
    }
    
    // Convert to uppercase for COBOL keywords
    std::string upperResult = result;
    for (char& c : upperResult) {
        c = std::toupper(c);
    }
    
    // Check if it's a keyword
    auto it = keywords.find(upperResult);
    if (it != keywords.end()) {
        return Token(it->second, result, line, startColumn);
    }
    
    return Token(TokenType::IDENTIFIER, result, line, startColumn);
}

Token Lexer::number() {
  int startColumn = column;
  std::string result;

  while(isValidPosition() && std::isdigit(peek())) {
    result += advance();
  }

  return Token(TokenType::NUMBER, result, line, startColumn);
}

Token Lexer::nextToken() {
  skipWhitespace();

  if (isAtEnd()) {
    return Token(TokenType::END_OF_FILE, "", line, column);
  }

  char c = peek();
  if (c == '\'') {
    return alphanumLiteral('\'');
  }

  if (c == '\"') {
    return alphanumLiteral('\"');
  }

  if (std::isalpha(c)) {
    return identifier();
  }

  if (std::isdigit(c)) {
    return number();
  }

  if (c == '.') {
    advance();
    return Token(TokenType::PERIOD, ".", line, column - 1);
  }

  advance();
  return Token(TokenType::INVALID, std::string(1, c), line, column - 1);
}

Token Lexer::peekToken() {
  size_t savedPos = pos;
  int savedLine = line;
  int savedColumn = column;

  Token token = nextToken();

  pos = savedPos;
  line = savedLine;
  column = savedColumn;

  return token;
}
