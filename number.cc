#include "number.h"
#include <sstream>

std::string clisp::number::str() const {
  std::ostringstream os; os << value(); return os.str();
}

clisp::expression_t clisp::number::eval(environment_t) const {
  return new number(this->value_);
}
