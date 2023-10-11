using P3F = valarray<llf>;
P3F toP3F(P3 p) { return {p.x, p.y, p.z}; }
llf dot(P3F a, P3F b) {
  return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}
P3F housev(P3 A, P3 B, int s) {
  const llf a = abs(A), b = abs(B);
  return toP3F(A) / a + s * toP3F(B) / b;
}
P project(P3 p, P3 q) {
  P3 o(0, 0, 1);
  P3F u = housev(q, o, q.z > 0 ? 1 : -1);
  auto pf = toP3F(p);
  auto np = pf - 2 * u * dot(u, pf) / dot(u, u);
  return P(np[0], np[1]);
} // project p onto the plane q^Tx = 0
