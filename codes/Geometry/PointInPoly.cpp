// C is convex polygon in counter-clockwise order
auto f = [&](P p) -> string {
  auto b1 = cross(C[1] - C[0], p - C[0]);
  auto b2 = cross(C[N - 1] - C[0], p - C[0]);
  if (b1 < 0 or b2 > 0) return "OUT";
  int L = 1, R = N - 1;
  while (L + 1 < R) {
    int M = (L + R) / 2;
    (cross(p - C[0], C[M] - C[0]) >= 0 ? R : L) = M;
  }
  auto v = cross(C[L] - p, C[R] - p);
  return v == 0 ? "ON" : v > 0 ? (b1 == 0 or b2 == 0 ? "ON" : "IN") : "OUT";
};
