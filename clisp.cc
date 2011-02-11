#include "sp.h"

#include <stdexcept>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <numeric>

namespace clisp {

  struct expression {
    expression();
    virtual ~expression();
    virtual double value() const;
    virtual std::string str() const;
    virtual sp<expression> apply(const std::list<sp<expression> > &es) const;
  };

  expression::expression() { std::cout << "created (" << this << ")" << std::endl; }

  expression::~expression() { std::cout << "destroyed (" << this << ")" <<  std::endl; }

  double expression::value() const {
    throw std::runtime_error("expression can not convert to value.");
  }

  std::string expression::str() const {
    return "expression";
  }

  struct sp<expression> expression::apply(const std::list<sp<expression> > &es) const {
    throw std::runtime_error("expression can not be applicable.");
  }

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

  namespace application {
    struct print : public expression {
      virtual sp<expression> apply(const std::list<sp<expression> > &es) const {
	std::for_each(es.begin(), es.end(), print_);
	return 0;
      }
      static void print_(const sp<expression> e) {
	std::cout << e->str() << std::endl;
      }
    };
    struct add : public expression {
      virtual sp<expression> apply(const std::list<sp<expression> > &es) const {
	std::list<sp<expression> >::const_iterator it = es.begin();
	const double init = (*it)->value();
	return new clisp::number(std::accumulate(++it, es.end(), init, accum_));
      }
      static double accum_(double v, const sp<expression> e) {
	return v + e->value();
      }
    };
  }
}

int main() {
  std::list<sp<clisp::expression> > es;
  es.push_back(new clisp::number(0.0));
  es.push_back(new clisp::number(1.0));
  es.push_back(new clisp::number(2.0));
  sp<clisp::expression> e = clisp::application::add().apply(es);
  std::cout << e->str() << std::endl;
  return 0;
}
