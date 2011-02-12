#include "environment.h"

#include <list>
#include <stdexcept>
#include <utility>

NS_CLISP_BEGIN

typedef std::pair<expression_t, expression_t> pair_t;

struct environment::impl : std::list<pair_t> {};

namespace {
  struct finder {
    explicit finder(const expression_t expr) : symbol(expr->str()) {}
    bool operator() (const pair_t &pair) const {
      return symbol == pair.first->str();
    }
  private:
    finder& operator= (const finder&);
    const std::string symbol;
  };
}


environment::environment() : o(new impl) {}

environment::environment(const environment &env) : o (new impl(*env.o)) {}

environment::~environment() { delete o; }

expression_t environment::find(const expression_t &expr) const
{
  const impl::const_iterator it = std::find_if(o->begin(), o->end(), finder(expr));
  if (o->end() == it)
    throw std::runtime_error("symbol not found in the environment");
  return it->second;
}

void environment::add(const expression_t &symbol, const expression_t &expr)
{
  o->push_front(std::make_pair(symbol, expr));
}

NS_CLISP_END

