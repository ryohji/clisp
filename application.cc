#include "application.h"
#include "number.h"

#include <algorithm>
#include <sstream>
#include <numeric>
#include <iostream>

namespace {

  void print_(const clisp::expression_t e) {
    std::cout << e->str() << std::endl;
  }

  double accum_(double v, clisp::expression_t e) {
    return v + e->value();
  }

}

clisp::expression_t clisp::application::print::apply(const list &es) const {
  std::for_each(es.begin(), es.end(), print_);
  return 0;
}

clisp::expression_t clisp::application::add::apply(const list &es) const {
  list::const_iterator it = es.begin();
  const double init = (*it)->value();
  return new clisp::number(std::accumulate(++it, es.end(), init, accum_));
}
