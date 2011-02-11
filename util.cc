#include <iostream>

template <typename TYPE>
struct sp {
  explicit sp(TYPE *o = 0) : c(new unsigned(1)), o(o) {}
  sp(const sp<TYPE>& u) : c(u.c), o(u.o) { ++*c; }
  ~sp() { detach(); }
  sp<TYPE>& operator=(const sp<TYPE>& u);
private:
  void detach();
  unsigned *c;
  TYPE *o;
};

template<typename TYPE>
inline sp<TYPE>& sp<TYPE>::operator=(const sp<TYPE>& u) {
  ++*u.c;
  detach();
  o = u.o;
  c = u.c;
}

template<typename TYPE>
inline void sp<TYPE>::detach() {
  if (0 == --*c) {
    delete c;
    delete o;
  }
}

struct object {
  object() { std::cout << "hello! (" << this << ")" << std::endl; }
  virtual ~object() { std::cout << "i'm dead (" << this << ")" << std::endl; }
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
  return 0;
}
