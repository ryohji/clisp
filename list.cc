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
    return "nil";
  } else {
    std::ostringstream os;
    const_iterator it = begin();
    os << "(" << (*it++)->str();
    while (end() != it) os << " " << (*it++)->str();
    os << ")";
    return os.str();
  }
}

expression_t list::apply(const list_t es) const {
  throw std::runtime_error("list itself can not be applicable");
}

namespace {
  list* evaluate(const list &l, environment_t env) {
    list* es = new list;
    list::const_iterator it = l.begin();
    while (l.end() != it)
      es->push_back((*it++)->eval(env));
    return es;
  }
}

expression_t list::eval(environment_t env) const {
  if (empty()) {
    return new list;
  } else {
    list_t es = evaluate(*this, env);
    expression_t app = es->front();
    es->pop_front();
    return app->apply(es);
  }
}

const list& list::as_list() const {
  return *this;
}

expression_t list::car() const {
  return front();
}

expression_t list::cdr() const {
  list *es = new list(*this); // copy
  es->pop_front(); // discard head member
  return es;
}

expression_t list::cons(expression_t expr) const {
  list *es = new list(*this); // copy
  es->push_front(expr);
  return es;
}

bool list::nil() const {
  return empty();
}


expression_t quote::eval(environment_t env) const {
  if (2 != size())
    throw std::runtime_error("quote does not just 2 expression");
  return *++begin();
}


expression_t define::eval(environment_t env) const {
  if (3 != size())
    throw std::runtime_error("define doesn't passed just 3 expressions");
  const_iterator symbol = ++begin();
  const_iterator expr = ++ (++begin());
  env->add(*symbol, (*expr)->eval(env));
  return 0;
}

NS_CLISP_END
