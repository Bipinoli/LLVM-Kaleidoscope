#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>

// lexer
// - unrecognized char is return as it is in ascii numbers
//   so the positive value in token means unknown character
enum Token {
  tok_eof = -1,
  tok_def = -2,
  tok_extern = -3,
  tok_identifier = -4,
  tok_number = -5,
};

static std::string identifier_str;
static double num_val;

/// gettok - return the next token from the standard input
static int get_tok() {
  static int last_char = ' ';
  while (isspace(last_char)) {
    last_char = getchar();
  }
  // identifier & keyword
  if (isalpha(last_char)) {
    identifier_str = last_char;
    while (isalnum((last_char = getchar()))) {
      identifier_str += last_char;
    }
    if (identifier_str == "def") {
      return tok_def;
    }
    if (identifier_str == "extern") {
      return tok_extern;
    }
    return tok_identifier;
  }
  // number
  if (isdigit(last_char) || last_char == '.') {
    std::string num_str;
    do {
      num_str += last_char;
      last_char = getchar();
    } while (isdigit(last_char) || last_char == '.');
    num_val = strtod(num_str.c_str(), 0);
    return tok_number;
  }
  // commment
  if (last_char == '#') {
    do {
      last_char = getchar();
    } while (last_char != EOF && last_char != '\n' && last_char != '\r');
    if (last_char != EOF) {
      return get_tok();
    }
  }
  // EOF
  if (last_char == EOF)
    return tok_eof;
  // unknown
  int unknown = last_char;
  last_char = getchar();
  return unknown;
}

int main() { printf("hi\n"); }
