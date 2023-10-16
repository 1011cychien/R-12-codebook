// does not work when n is prime or n == 1
// return any non-trivial factor
llu pollard_rho(llu n) {
  static mt19937_64 rnd(120821011);
  if (!(n & 1)) return 2;
  llu y = 2, z = y, c = rnd() % n, p = 1, i = 0, t;
  auto f = [&](llu x) {
    return madd(mmul(x, x, n), c, n); };
  do {
    p = mmul(msub(z = f(f(z)), y = f(y), n), p, n);
    if (++i &= 63) if (i == (i & -i)) t = gcd(p, n);
  } while (t == 1);
  return t == n ? pollard_rho(n) : t;
} // test @ yosupo judge
