#include <iostream>

struct util {
  explicit util(struct object *o = 0) : c(new unsigned(1)), o(o) {}
  util(const util& u) : c(u.c), o(u.o) { ++*c; }
  ~util() { detach(); }
  util& operator=(const util& u);
private:
  void detach();
  unsigned *c;
  struct object *o;
};

struct object {
  object() { std::cout << "hello! (" << this << ")" << std::endl; }
  virtual ~object() { std::cout << "i'm dead (" << this << ")" << std::endl; }
};

inline util& util::operator=(const util& u) {
  ++*u.c;
  detach();
  o = u.o;
  c = u.c;
}

inline void util::detach() {
  if (0 == --*c) {
    delete c;
    delete o;
  }
}

int main() {
  { // test ctor
    util u(new object);
  }
  { // test copy ctor
    util u(new object);
    util c = u;
  }
  { // test assignment
    util u(new object), a;
    a = u;
  }
  { // test self assignment
    util u(new object);
    u = u;
  }
  return 0;
}
