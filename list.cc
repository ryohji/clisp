#include "list.h"
#include <stdexcept>
#include <sstream>

NS_CLISP_BEGIN

double list::value() const {
  throw std::runtime_error("list can not convert to value");
}

std::string list::str() const {
  if (empty()) {
    return "()";
  } else {
    std::ostringstream os;
    const_iterator it = begin();
    os << "(" << (*it++)->str();
    while (end() != it) os << " " << (*it++)->str();
    os << ")";
    return os.str();
  }
}

expression_t list::apply(const list &es) const {
  return 0;
}

expression_t list::eval(environment_t env) const {
  return 0;
}

NS_CLISP_END
