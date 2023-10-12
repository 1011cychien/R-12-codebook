struct Face {
  int a, b, c;
  Face(int ta, int tb, int tc) : a(ta), b(tb), c(tc) {}
};
void preprocess(vector<P3> &pt) {
  // ensure first 4 points are not coplanar
#define S(I, E...) swap(pt[I], \
    *find_if(all(pt), [&](auto z) { return E; }))
  S(1, pt[0] != z);
  S(2, ver(z, pt[0], pt[1]) != P3(0, 0, 0));
  S(3, volume(z, pt[0], pt[1], pt[2]) != 0);
}
// return the faces with pt indexes
// all points coplanar case will WA
vector<Face> convex_hull_3D(vector<P3> pt) {
  const int n = int(pt.size());
  if (n <= 3) return {}; // be careful about edge case
  preprocess(pt); vector<Face> now;
  vector<vector<int>> z(n, vector<int>(n));
  now.emplace_back(0, 1, 2); now.emplace_back(2, 1, 0);
  for (int i = 3; i < n; i++) {
    vector<Face> next;
    for (const auto &f : now) {
      lld d = volume(pt[f.a], pt[f.b], pt[f.c], pt[i]);
      if (d <= 0) next.push_back(f);
      z[f.a][f.b] = z[f.b][f.c] = z[f.c][f.a] = sgn(d);
    }
    const auto F = [&](int x, int y) {
      if (z[x][y] > 0 && z[y][x] <= 0)
        next.emplace_back(x, y, i);
    };
    for (const auto &f : now)
      F(f.a, f.b), F(f.b, f.c), F(f.c, f.a);
    now = next;
  }
  return now;
}
// n^2 delaunay: facets with negative z normal of
// convexhull of (x, y, x^2 + y^2), use a pseudo-point
// (0, 0, inf) to avoid degenerate case
// test @ SPOJ CH3D
// llf area = 0, vol = 0; // surface area / volume
// for (auto [a, b, c]: faces) {
//   area += abs(ver(p[a], p[b], p[c]));
//   vol += volume(P3(0, 0, 0), p[a], p[b], p[c])
// }
// area /= 2; vol /= 6;

