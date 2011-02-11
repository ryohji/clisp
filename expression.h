#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "sp.h"

#include <list>
#include <stdexcept>
#include <string>

#define NS_CLISP_BEGIN namespace clisp {
#define NS_CLISP_END } /* END namespace clisp */

NS_CLISP_BEGIN

struct expression;
typedef sp<clisp::expression> expression_t;

typedef std::list<expression_t> list;

struct expression {
  virtual ~expression();
  virtual double value() const;
  virtual std::string str() const;
  virtual expression_t apply(const list &es) const;
};

inline expression::~expression() {}

inline double expression::value() const {
  throw std::runtime_error("expression can not convert to value.");
}

inline std::string expression::str() const {
  return "expression";
}

inline expression_t expression::apply(const list &es) const {
  throw std::runtime_error("expression can not be applicable.");
}

NS_CLISP_END

#endif /* EXPRESSION_H_ */
