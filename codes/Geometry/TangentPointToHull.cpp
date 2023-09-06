pair<int, int> get_tangent(const vector<P> &v, P p) {
  const auto gao = [&, N = int(v.size())](int s) {
    const auto lt = [&](int x, int y) {
      return ori(p, v[x % N], v[y % N]) == s; };
    int l = 0, r = N; bool up = lt(0, 1);
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (lt(m, 0) ? up : !lt(m, m+1)) r = m;
      else l = m;
    }
    return (lt(l, r) ? r : l) % N;
  }; // test @ codeforces.com/gym/101201/problem/E
  return {gao(-1), gao(1)}; // (a,b):ori(p,v[a],v[b])<0
} // plz ensure that point strictly out of hull
