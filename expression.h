#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "sp.h"

#include <string>

#define NS_CLISP_BEGIN namespace clisp {
#define NS_CLISP_END } /* END namespace clisp */

NS_CLISP_BEGIN

struct expression;
typedef sp<expression> expression_t;

struct environment;
typedef sp<environment> environment_t;

struct list;
typedef sp<list> list_t;

struct expression {
  virtual ~expression();
  virtual double value() const;
  virtual std::string str() const;
  virtual expression_t apply(const list_t es) const;
  virtual expression_t eval(environment_t env) const;
  virtual const list& as_list() const;
  virtual bool as_boolean() const;
};

NS_CLISP_END

#endif /* EXPRESSION_H_ */
