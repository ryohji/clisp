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
  env->add(new clisp::symbol("list"), new clisp::application::list_make);
  env->add(new clisp::symbol("null?"), new clisp::application::list_is_null);
  env->add(new clisp::symbol("car"), new clisp::application::list_car);
  env->add(new clisp::symbol("cdr"), new clisp::application::list_cdr);
  env->add(new clisp::symbol("cons"), new clisp::application::list_cons);
  env->add(new clisp::symbol("nil"), new clisp::list);
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

  try {
    std::stringstream input("(cons 1 (cons 2 ()))");
    std::cout << clisp::read(input)->eval(env)->str() << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  try {
    std::stringstream input("(list (quote list) 1 2 3)");
    std::cout << clisp::read(input)->eval(env)->str() << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
