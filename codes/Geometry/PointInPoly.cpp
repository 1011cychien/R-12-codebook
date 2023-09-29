bool PIP(const vector<P> &p, P z, bool strict = true) {
  int cnt = 0, n = (int)p.size();
  for (int i = 0; i < n; i++) {
    P A = p[i], B = p[(i + 1) % n];
    if (isInter(Seg(A, B), z)) return !strict;
    auto zy = IM(z), Ay = IM(A), By = IM(B);
    cnt ^= ((zy<Ay) - (zy<By)) * ori(z, A, B) > 0;
  }
  return cnt;
}
