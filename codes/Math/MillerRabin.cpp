bool isprime(llu x) {
  auto witn = [&](llu a, int t) {
    for (llu a2; t--; a = a2) {
      a2 = mmul(a, a, x);
      if (a2 == 1 && a != 1 && a != x - 1) return true;
    }
    return a != 1;
  };
  if (x <= 2 || ~x & 1) return x == 2;
  int t = countr_zero(x-1); llu odd = (x-1) >> t;
  for (llu m:
    {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
    if (m % x != 0 && witn(mpow(m % x, odd, x), t))
      return false;
  return true;
} // test @ luogu 143 & yosupo judge
