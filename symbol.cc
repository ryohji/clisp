#include "symbol.h"
#include "environment.h"

clisp::expression_t clisp::symbol::eval(environment_t env) const {
  return env->find(s_);
}
