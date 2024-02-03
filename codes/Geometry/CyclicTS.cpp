int cyclic_ternary_search(int N, auto &&lt_) {
  auto lt = [&](int x, int y) {
    return lt_(x % N, y % N); }
  int l = 0, r = N; bool up = lt(0, 1);
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (lt(m, 0) ? up : !lt(m, m+1)) r = m;
    else l = m;
  }
  return (lt(l, r) ? r : l) % N;
}
