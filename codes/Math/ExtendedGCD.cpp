// ax+ny = 1, ax+ny == ax == 1 (mod n)
tuple<lld,lld,lld> exgcd(lld x, lld y) {
  if (y == 0) return {x, 1, 0};
  auto [g, b, a] = exgcd(y, x % y);
  return {g, a, b - (x / y) * a};
}
