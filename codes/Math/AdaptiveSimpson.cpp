llf integrate(auto &&f, llf L, llf R) {
  auto simp = [&](llf l, llf r) {
    llf m = (l + r) / 2;
    return (f(l) + f(r) + 4.0 * f(m)) * (r - l) / 6.0;
  };
  auto F = [&](auto Y, llf l, llf r, llf v, llf eps) {
    llf m = (l+r)/2, vl = simp(l, m), vr = simp(m, r);
    if (abs(vl + vr - v) <= 15 * eps)
      return vl + vr + (vl + vr - v) / 15.0;
    return Y(Y, l, m, vl, eps / 2.0) +
                  Y(Y, m, r, vr, eps / 2.0);
  };
  return F(F, L, R, simp(L, R), 1e-6);
}
