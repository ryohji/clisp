#ifndef SP_H_
#define SP_H_

template <typename TYPE>
struct sp {
  sp(TYPE *o = 0) : c(new unsigned(1)), o(o) {}
  sp(const sp<TYPE>& u) : c(u.c), o(u.o) { ++*c; }
  ~sp() { detach(); }
  sp<TYPE>& operator=(const sp<TYPE>& u);
  const TYPE* operator->() const { return o; }
  TYPE* operator->();
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

template<typename TYPE>
inline TYPE* sp<TYPE>::operator->() {
  return const_cast<TYPE*>(static_cast<const sp<TYPE>&>(*this).operator->());
}

#endif /* SP_H_ */
