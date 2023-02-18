constexpr size_t L = 800'000'000;
uint8_t buf[L], *buf_p;
size_t buf_sz;
template <typename T> struct Alloc {
  using value_type = T;
  using is_always_equal = std::true_type;
  template <typename U> struct rebind { using other = Alloc<U>; };
  Alloc() = default;
  template <typename U> Alloc(const Alloc<U> &) {}
  template <typename U> bool operator==(const Alloc<U> &) { return true; }
  template <typename U> bool operator!=(const Alloc<U> &) { return false; }
  T *allocate(size_t n) {
    auto *old_p =
        (uint8_t *)align(alignof(T), sizeof(T), (void *&)buf_p, buf_sz);
    buf_p += sizeof(T) * n;
    return (T *)old_p;
  }
  void deallocate(T *, size_t) {}
};
// init: buf_p = buf, buf_sz = L
