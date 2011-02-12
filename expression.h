#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "sp.h"

#include <list>
#include <string>

#define NS_CLISP_BEGIN namespace clisp {
#define NS_CLISP_END } /* END namespace clisp */

NS_CLISP_BEGIN

struct expression;
typedef sp<expression> expression_t;

struct environment;
typedef sp<environment> environment_t;

typedef std::list<expression_t> list;

struct expression {
  virtual ~expression();
  virtual double value() const;
  virtual std::string str() const;
  virtual expression_t apply(const list &es) const;
  virtual expression_t eval(environment_t env) const;
};

NS_CLISP_END

#endif /* EXPRESSION_H_ */
