#ifndef NUMBER_H_
#define NUMBER_H_

#include "expression.h"

NS_CLISP_BEGIN

struct number : public expression {
  number() : value_(0) {}
  explicit number(double value) : value_(value) {}
  virtual double value() const { return value_; }
  virtual std::string str() const;
private:
  double value_;
};

NS_CLISP_END

#endif /* NUMBER_H_ */

