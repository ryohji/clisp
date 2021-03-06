#include "expression.h"

#include <stdexcept>

clisp::expression::~expression() {}

double clisp::expression::value() const {
  throw std::runtime_error("expression can not convert to value.");
}

std::string clisp::expression::str() const {
  return "expression";
}

clisp::expression_t clisp::expression::apply(const list_t es) const {
  throw std::runtime_error("expression " + str() + " can not be applicable.");
}

clisp::expression_t clisp::expression::eval(environment_t e) const {
  throw std::runtime_error("expression can not be evaluatable.");
}

const clisp::list& clisp::expression::as_list() const {
  throw std::runtime_error("expression is not type of list.");
}

bool clisp::expression::as_boolean() const {
  throw std::runtime_error("expression is not type of boolean.");
}
