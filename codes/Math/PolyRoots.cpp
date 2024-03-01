VD polyRoots(VD p, llf xmin, llf xmax) {
  if (p.size() == 2) return {-p[0]/p[1]};
  VD d = polyRoots(derivative(p), xmin, xmax), ret;
  d.pb(xmin-1); d.pb(xmax+1); sort(all(d));
  for (size_t i = 0; i + 1 < d.size(); i++) {
    llf l = d[i], h = d[i+1]; bool s = eval(p, l) > 0;
    if (s ^ (eval(p, h) > 0)) {
      for (int _ = 0; _ < 60; _++) {
        llf m = (l + h) / 2, f = eval(p, m);
        ((f <= 0) ^ s ? l : h) = m;
      }
      ret.push_back((l + h) / 2);
    }
  }
  return ret;
}
