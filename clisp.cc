#include <stdexcept>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <numeric>

struct expression {
  virtual ~expression();
  virtual double value() const;
  virtual std::string str() const;
  virtual struct expression* apply(const std::list<expression*> &es) const;
};

expression::~expression() {}

double expression::value() const {
  throw std::runtime_error("expression can not convert to value.");
}

std::string expression::str() const {
  return "expression";
}

struct expression* expression::apply(const std::list<expression*> &es) const {
  throw std::runtime_error("expression can not be applicable.");
}

namespace clisp {
  struct number : public expression {
    number() : value_(0) {}
    explicit number(double value) : value_(value) {}
    virtual double value() const { return value_; }
    virtual std::string str() const {
      std::ostringstream os; os << value(); return os.str();
    }
  private:
    double value_;
  };
}

namespace application {
  struct print : public expression {
    virtual struct expression* apply(const std::list<expression*> &es) const {
      std::for_each(es.begin(), es.end(), print_);
      return 0;
    }
    static void print_(const expression* e) {
      std::cout << e->str() << std::endl;
    }
  };
  struct add : public expression {
    virtual struct expression* apply(const std::list<expression*> &es) const {
      std::list<expression*>::const_iterator it = es.begin();
      const double init = (*it)->value();
      return new clisp::number(std::accumulate(++it, es.end(), init, accum_));
    }
    static double accum_(double v, const expression* e) {
      return v + e->value();
    }
  };
}

int main() {
  clisp::number n0(0), n1(1), n2(2);
  std::list<expression*> es;
  es.push_back(&n0);
  es.push_back(&n1);
  es.push_back(&n2);
  expression *e = application::add().apply(es);
  std::cout << e->str() << std::endl;
  delete e;
  return 0;
}
