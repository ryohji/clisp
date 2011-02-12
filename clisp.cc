#include "expression.h"
#include "number.h"
#include "application.h"
#include "environment.h"
#include "symbol.h"

#include <iostream>

int main() {
  clisp::list es;
  es.push_back(new clisp::number(0.0));
  es.push_back(new clisp::number(1.0));
  es.push_back(new clisp::number(2.0));
  clisp::expression_t e = clisp::application::add().apply(es);
  std::cout << e->str() << std::endl;

  clisp::environment_t env(new clisp::environment);
  env->add(new clisp::symbol("+"), new clisp::application::add);
  env->add(new clisp::symbol("pi"), new clisp::number(3.14));
  e = env->find("pi");
  std::cout << e->str() << std::endl;
  return 0;
}
