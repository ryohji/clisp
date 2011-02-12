#include "list.h"
#include "environment.h"
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
  throw std::runtime_error("list can not be applicable");
}

namespace {
  list* evaluate(const list &l, environment_t env) {
    list* es = new list;
    list::const_iterator it = l.begin();
    while (l.end() != it)
      es->push_back((*it++)->eval(env));
    return es;
  }

  template<typename T> inline T pop_front(std::list<T> &l)
  { T value = l.front(); l.pop_front(); return value; }
}

expression_t list::eval(environment_t env) const {
  if (empty()) {
    throw std::runtime_error("() can not be evaluatable");
  } else {
    list* es = evaluate(*this, env);
    expression_t lst(es); // for auto deletion, when poping out this scope
    expression_t app = clisp::pop_front(*es);
    return app->apply(*es);
  }
}

NS_CLISP_END
