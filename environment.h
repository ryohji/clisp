#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "expression.h"

NS_CLISP_BEGIN

struct environment {
  environment();

  environment(const environment& env);

  ~environment();

  /* find matching expression to expr as symbol. if not found, throw runtime_error. */
  expression_t find(const expression_t &expr) const;

  void add(const expression_t &symbol, const expression_t &expr);

private:
  /* disable assignment */
  environment& operator= (const environment &);

  struct impl;
  impl *o;
};

NS_CLISP_END

#endif /* ENVIRONMENT_H_ */
