bool PIP(vector<P> &p, P z, bool strict = true) {
  int cnt = 0, n = p.size();
  for (int i = 0; i < n; i++) {
    P A = p[i], B = p[(i + 1) % n];
    if (isInter(Segment(A, B), z)) return !strict;
    cnt ^= ((z.y<A.y) - (z.y<B.y)) * ori(z, A, B) > 0;
  }
  return cnt;
}
