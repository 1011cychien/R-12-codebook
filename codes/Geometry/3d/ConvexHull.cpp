struct Face {
  int a, b, c;
  Face(int ta, int tb, int tc) : a(ta), b(tb), c(tc) {}
};
auto preprocess(const vector<P3> &pt) {
  auto G = pt.begin();
  auto a = find_if(all(pt), [&](P3 z) {
    return z != *G; }) - G;
  auto b = find_if(all(pt), [&](P3 z) {
    return ver(*G, pt[a], z) != P3(0, 0, 0); }) - G;
  auto c = find_if(all(pt), [&](P3 z) {
    return volume(*G, pt[a], pt[b], z) != 0; }) - G;
  vector<size_t> id;
  for (size_t i = 0; i < pt.size(); i++)
    if (i != a && i != b && i != c) id.push_back(i);
  return tuple{a, b, c, id};
}
// return the faces with pt indexes
// all points coplanar case will WA
vector<Face> convex_hull_3D(const vector<P3> &pt) {
  const int n = int(pt.size());
  if (n <= 3) return {}; // be careful about edge case
  vector<Face> now;
  vector<vector<int>> z(n, vector<int>(n));
  auto [a, b, c, ord] = preprocess(pt);
  now.emplace_back(a, b, c); now.emplace_back(c, b, a);
  for (auto i : ord) {
    vector<Face> next;
    for (const auto &f : now) {
      lld v = volume(pt[f.a], pt[f.b], pt[f.c], pt[i]);
      if (v <= 0) next.push_back(f);
      z[f.a][f.b] = z[f.b][f.c] = z[f.c][f.a] = sgn(v);
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
// for (auto [a, b, c]: faces)
//   area += abs(ver(p[a], p[b], p[c]))/2.0,
//   vol += volume(P3(0, 0, 0), p[a], p[b], p[c])/6.0;
