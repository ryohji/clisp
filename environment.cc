#include "environment.h"

#include <algorithm>
#include <list>
#include <stdexcept>
#include <utility>
#include <string>

NS_CLISP_BEGIN

typedef std::pair<std::string, expression_t> pair_t;

struct environment::impl : std::list<pair_t> {};

namespace {
  struct finder {
    explicit finder(const std::string& expr) : symbol(expr) {}
    bool operator() (const pair_t &pair) const {
      return symbol == pair.first;
    }
  private:
    finder& operator= (const finder&);
    const std::string& symbol;
  };
}


environment::environment() : o(new impl) {}

environment::environment(const environment &env) : o (new impl(*env.o)) {}

environment::~environment() { delete o; }

expression_t environment::find(const std::string &symbol) const {
  const impl::const_iterator it = std::find_if(o->begin(), o->end(), finder(symbol));
  if (o->end() == it)
    throw std::runtime_error("symbol not found in the environment");
  return it->second;
}

void environment::add(const expression_t &symbol, const expression_t &expr) {
  // TODO: need to check 1st argument type
  o->push_front(std::make_pair(symbol->str(), expr));
}

NS_CLISP_END
