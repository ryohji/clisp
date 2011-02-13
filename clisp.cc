#include "expression.h"
#include "number.h"
#include "application.h"
#include "environment.h"
#include "symbol.h"
#include "list.h"
#include "read.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

int main() {
  clisp::environment_t env(new clisp::environment);
  env->add(new clisp::symbol("+"), new clisp::application::add);
  env->add(new clisp::symbol("pi"), new clisp::number(3.14));

  clisp::list_t es(new clisp::list);
  es->push_back(new clisp::symbol("+"));
  es->push_back(new clisp::number(1.0));
  es->push_back(new clisp::number(2.0));
  es->push_back(new clisp::number(3.0));
  std::cout << es->str() << " evaluated as " << es->eval(env)->str() << std::endl;

  try {
    std::stringstream input("(+ 1 2 3 4 5 6 7 8 9 10)");
    std::cout << clisp::read(input)->eval(env)->str() << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
