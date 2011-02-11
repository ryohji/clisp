#include "expression.h"
#include "number.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <numeric>

namespace clisp {

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
