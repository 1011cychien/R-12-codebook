pair<int, int> get_tangent(const vector<P> &v, P p) {
  auto gao = [&](int s) {
    return cyclic_ternary_search([&](int x, int y) {
      return ori(p, v[x], v[y]) == s;
    });
  }; // test @ codeforces.com/gym/101201/problem/E
  return {gao(-1), gao(1)}; // (a,b):ori(p,v[a],v[b])<0
} // plz ensure that point strictly out of hull
    // if colinear, returns arbitrary point on line
