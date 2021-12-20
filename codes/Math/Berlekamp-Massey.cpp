template <typename T>
vector<T> BerlekampMassey(const vector<T> &output) {
  std::vector<T> d(output.size() + 1), me, he;
  size_t fhe = 0;
  for (size_t i = 1; i <= output.size(); ++i) {
    for (size_t j = 0; j < me.size(); ++j)
      d[i] += output[i - j - 2] * me[j];
    if ((d[i] -= output[i - 1]) == 0) continue;
    if (me.empty()) {
      me.resize(fhe = i);
      continue;
    }
    std::vector<T> o(i - fhe - 1);
    T k = -d[i] / d[fhe]; o.push_back(-k);
    for (T x : he) o.push_back(x * k);
    if (o.size() < me.size()) o.resize(me.size());
    for (size_t j = 0; j < me.size(); ++j) o[j] += me[j];
    if (i-fhe+he.size() >= me.size()) he = me, fhe = i;
    me = o;
  }
  return me;
}
