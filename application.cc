#include "application.h"
#include "number.h"
#include "list.h"
#include "symbol.h"

#include <algorithm>
#include <sstream>
#include <numeric>
#include <iostream>
#include <stdexcept>

namespace {
  void print_(const clisp::expression_t e) {
    std::cout << e->str() << std::endl;
  }
}


std::string clisp::application::print::str() const {
  return "print :: aplication";
}

clisp::expression_t clisp::application::print::apply(const list_t es) const {
  std::for_each(es->begin(), es->end(), print_);
  return 0;
}


namespace {
  double accum_(double v, clisp::expression_t e) {
    return v + e->value();
  }
}

std::string clisp::application::add::str() const {
  return "add :: application";
}

clisp::expression_t clisp::application::add::apply(const list_t es) const {
  list::const_iterator it = es->begin();
  const double init = (*it)->value();
  return new clisp::number(std::accumulate(++it, es->end(), init, accum_));
}


std::string clisp::application::list_make::str() const {
  return "list :: application";
}


clisp::expression_t clisp::application::list_make::apply(const list_t es) const {
  list *l = 0;
  if (0 < es->size()) {
    std::string s = (*es->begin())->str();
    if ("quote" == s) l = new quote;
    if ("define" == s) l = new define;
  }
  if (!l) l = new list;
  list::const_iterator it = es->begin();
  while (es->end() != it) l->push_back(*it++);
  return l;
}

std::string clisp::application::list_is_null::str() const {
  return "null? :: application";
}

clisp::expression_t clisp::application::list_is_null::apply(const list_t es) const {
  if (1 != es->size())
    throw std::runtime_error("passed not just one expression");
  return new symbol( (*es->begin())->as_list().nil() ? "t" : "f" );
}


std::string clisp::application::list_car::str() const {
  return "car :: application";
}

clisp::expression_t clisp::application::list_car::apply(const list_t es) const {
  if (1 != es->size())
    throw std::runtime_error("passed not just one expression");
  return (*es->begin())->as_list().car();
}


std::string clisp::application::list_cdr::str() const {
  return "cdr :: application";
}

clisp::expression_t clisp::application::list_cdr::apply(const list_t es) const {
  if (1 != es->size())
    throw std::runtime_error("passed not just one expression");
  return (*es->begin())->as_list().cdr();
}


std::string clisp::application::list_cons::str() const {
  return "cons :: application";
}

clisp::expression_t clisp::application::list_cons::apply(const list_t es) const {
  if (2 != es->size())
    throw std::runtime_error("passed not two expression");
  try {
    list::const_iterator first = es->begin(), second = first;
    std::advance(second, 1);
    return (*second)->as_list().cons(*first);
  } catch (const std::runtime_error&) {
    throw std::runtime_error("passed non-list expression as 2nd argument");
  }
}
