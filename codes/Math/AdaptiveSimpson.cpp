llf simp(llf l, llf r) {
  llf m = (l + r) / 2;
  return (f(l) + f(r) + 4.0 * f(m)) * (r - l) / 6.0;
}
llf F(llf L, llf R, llf v, llf eps) {
  llf M = (L + R) / 2, vl = simp(L, M), vr = simp(M, R);
  if (abs(vl + vr - v) <= 15 * eps)
    return vl + vr + (vl + vr - v) / 15.0;
  return F(L, M, vl, eps / 2.0) +
         F(M, R, vr, eps / 2.0);
} // call F(l, r, simp(l, r), 1e-6)
