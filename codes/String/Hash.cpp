template <int P = 127, int Q = 1051762951>
class Hash {
  vector<int> h, p;
public:
  Hash(const auto &s) : h(s.size()+1), p(s.size()+1) {
    for (size_t i = 0; i < s.size(); ++i)
      h[i + 1] = add(mul(h[i], P), s[i]);
    generate(all(p), [x = 1, y = 1, this]() mutable {
      return y = x, x = mul(x, P), y; });
  }
  int query(int l, int r) const { // 0-base [l, r)
    return sub(h[r], mul(h[l], p[r - l]));
  }
};
