#ifndef READ_H_
#define READ_H_

#include "expression.h"
#include <iostream>

NS_CLISP_BEGIN

/* read string as S expression, return expression_t */
expression_t read(std::istream &S);

NS_CLISP_END

#endif /* READ_H_ */
