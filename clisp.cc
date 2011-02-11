#include "expression.h"
#include "number.h"
#include "application.h"

#include <iostream>

int main() {
  clisp::list es;
  es.push_back(new clisp::number(0.0));
  es.push_back(new clisp::number(1.0));
  es.push_back(new clisp::number(2.0));
  clisp::expression_t e = clisp::application::add().apply(es);
  std::cout << e->str() << std::endl;
  return 0;
}
