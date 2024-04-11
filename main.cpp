#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// ---------- LEXER
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

// ------ PARSER
class ExprAST {
public:
  virtual ~ExprAST() = default;
};

class NumExprAST : public ExprAST {
  double val;

public:
  NumExprAST(double val) : val(val) {}
};

class VariableExprAST : public ExprAST {
  std::string name;

public:
  VariableExprAST(std::string &name) : name(name) {}
};

class BinaryExprAST : public ExprAST {
  char op;
  std::unique_ptr<ExprAST> lhs, rhs;

public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                std::unique_ptr<ExprAST> rhs)
      : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class FuncCallExprAST : public ExprAST {
  std::string callee;
  std::vector<std::unique_ptr<ExprAST>> args;

public:
  FuncCallExprAST(const std::string &callee,
                  std::vector<std::unique_ptr<ExprAST>> args)
      : callee(callee), args(std::move(args)) {}
};

class FuncPrototypeAST {
  std::string name;
  std::vector<std::string> args;

public:
  FuncPrototypeAST(std::string &name, std::vector<std::string> args)
      : name(name), args(std::move(args)) {}

  const std::string &getName() const { return name; }
};

class FuncDefAST {
  std::unique_ptr<FuncPrototypeAST> proto;
  std::unique_ptr<ExprAST> body;

public:
  FuncDefAST(std::unique_ptr<FuncPrototypeAST> proto,
             std::unique_ptr<ExprAST> body)
      : proto(std::move(proto)), body(std::move(body)) {}
};

int main() { printf("hi\n"); }
