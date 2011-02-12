#include "expression.h"

#include <stdexcept>

clisp::expression::~expression() {}

double clisp::expression::value() const {
  throw std::runtime_error("expression can not convert to value.");
}

std::string clisp::expression::str() const {
  return "expression";
}

clisp::expression_t clisp::expression::apply(const clisp::list &es) const {
  throw std::runtime_error("expression can not be applicable.");
}

clisp::expression_t clisp::expression::eval(environment_t e) const {
  throw std::runtime_error("expression can not be evaluatable.");
}
