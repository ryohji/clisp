#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "expression.h"

#include <string>

NS_CLISP_BEGIN

struct symbol : public expression {
  explicit symbol(const std::string &symb);
  virtual std::string str() const;
private:
  symbol();
  const std::string s_;
};

inline symbol::symbol(const std::string &symb) : s_(symb) {}

inline std::string symbol::str() const { return s_; }

NS_CLISP_END

#endif /* SYMBOL_H_ */
