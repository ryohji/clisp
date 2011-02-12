#ifndef LIST_H_
#define LIST_H_

#include "expression.h"
#include <list>

NS_CLISP_BEGIN

struct list : public expression, public std::list<expression_t> {
  virtual double value() const;
  virtual std::string str() const;
  virtual expression_t apply(const list_t es) const;
  virtual expression_t eval(environment_t env) const;
};

NS_CLISP_END

#endif /* LIST_H_ */
