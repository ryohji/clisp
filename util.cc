#include "sp.h"
#include <iostream>

struct object {
  object() { std::cout << "hello! (" << this << ")" << std::endl; }
  virtual ~object() { std::cout << "i'm dead (" << this << ")" << std::endl; }
  void hello() const { std::cout << "hello" << std::endl; }
  void mutable_hello() { hello(); }
};

int main() {
  { // test ctor
    sp<object> u(new object);
  }
  { // test copy ctor
    sp<object> u(new object);
    sp<object> c = u;
  }
  { // test assignment
    sp<object> u(new object), a;
    a = u;
  }
  { // test self assignment
    sp<object> u(new object);
    u = u;
  }
  { // test cast operator
    sp<object> u(new object);
    u->hello();
    u->mutable_hello();
  }
  return 0;
}
