#pragma once
#include <string>
#include <vector>


enum class TokenType {

  // Division keywords
  IDENTIFICATION,
  PROGRAM_ID,
  DATA,
  PROCEDURE,


  // Basic elements
  IDENTIFIER,
  NUMBER,
  PERIOD,

  // ALPHANUMERIC LITERALS
  STANDARD_ALPHANUM,
  HEXADEC_ALPHANUM,
  NULL_TERM_ALPHANUM,

  //FORMATERS
  Z,
  X,
  
  // EOF
  END_OF_FILE,

  // ERROR
  INVALID
};


struct Token {
  std::string lexeme;
  TokenType type;

  int line;
  int column;

  Token(TokenType t, std::string lex, int ln, int col)
    : type(t), lexeme(std::move(lex)), line(ln), column(col) {}
};


class Lexer {
public:
  explicit Lexer(std::string input);

  Token nextToken();
  Token peekToken();

private:
  std::string source;
  size_t pos = 0;
  int line = 1;
  int column = 1;

  char advance();
  char peek() const;
  void skipWhitespace();
  //void skipComment();
  bool isAtEnd() const;

  Token identifier();
  Token number();

  bool isValidPosition() const {
    return pos < source.length();
  }
};

