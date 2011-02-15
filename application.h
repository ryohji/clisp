#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "expression.h"

NS_CLISP_BEGIN

namespace application {

  struct print : public expression {
    virtual std::string str() const;
    virtual expression_t apply(const list_t es) const;
  };

  struct add : public expression {
    virtual std::string str() const;
    virtual expression_t apply(const list_t es) const;
  };

  struct list_is_list : public expression {
    virtual std::string str() const;
    virtual expression_t apply(const list_t es) const;
  };

  struct list_is_null : public expression {
    virtual std::string str() const;
    virtual expression_t apply(const list_t es) const;
  };

  struct list_car : public expression {
    virtual std::string str() const;
    virtual expression_t apply(const list_t es) const;
  };

  struct list_cdr : public expression {
    virtual std::string str() const;
    virtual expression_t apply(const list_t es) const;
  };

  struct list_cons : public expression {
    virtual std::string str() const;
    virtual expression_t apply(const list_t es) const;
  };

}

NS_CLISP_END

#endif /* APPLICATION_H_ */
