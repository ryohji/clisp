#ifndef SP_H_
#define SP_H_

template <typename TYPE>
struct sp {
  sp(TYPE *o = 0);
  sp(const sp<TYPE>& u);
  ~sp() { detach(); }
  sp<TYPE>& operator=(const sp<TYPE>& u);
  TYPE* operator->();
  const TYPE* operator->() const { return o; }
private:
  void detach();
  TYPE *o;
};

namespace sp_detail {
  unsigned ref_up(void *);
  unsigned ref_down(void *);
}

template<typename TYPE>
inline sp<TYPE>::sp(TYPE *o) : o(o) {
  sp_detail::ref_up(o);
}

template<typename TYPE>
inline sp<TYPE>::sp(const sp<TYPE>& u) : o(u.o) {
  sp_detail::ref_up(o);
}


template<typename TYPE>
inline sp<TYPE>& sp<TYPE>::operator=(const sp<TYPE>& u) {
  sp_detail::ref_up(u.o);
  detach();
  o = u.o;
}

template<typename TYPE>
inline void sp<TYPE>::detach() {
  if (0 == sp_detail::ref_down(o)) {
    delete o;
  }
}

template<typename TYPE>
inline TYPE* sp<TYPE>::operator->() {
  return const_cast<TYPE*>(static_cast<const sp<TYPE>&>(*this).operator->());
}

#endif /* SP_H_ */
