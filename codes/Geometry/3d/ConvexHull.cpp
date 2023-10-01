// return the faces with pt indexes
struct P3 { lld x,y,z;
  P3 operator * (const P3 &b) const {
    return(P3){y*b.z-b.y*z,z*b.x-b.z*x,x*b.y-b.x*y};
  } };
struct Face { int a, b, c;
  Face(int ta,int tb,int tc):a(ta),b(tb),c(tc){} };
P3 ver(P3 a, P3 b, P3 c) { return (b - a) * (c - a); }
// all points coplanar case will WA
vector<Face> convex_hull_3D(vector<P3> pt) {
  int n = int(pt.size()); vector<Face> now;
  if (n <= 2) return {}; // be careful about edge case
  // ensure first 4 points are not coplanar
#define S(I, E...) swap(pt[I], *find_if(all(pt), \
      [&](auto z) { return E; }))
  S(1, pt[0] != z);
  S(2, ver(z, pt[0], pt[1]) != (P3){0, 0, 0});
  S(3, (z - pt[0]).dot(ver(pt[0], pt[1], pt[2])) != 0);
  vector<vector<int>> flag(n, vector<int>(n));
  now.emplace_back(0,1,2); now.emplace_back(2,1,0);
  for (int i = 3; i < n; i++) {
    vector<Face> next;
    for (const auto &f : now) {
      lld d = (pt[i] - pt[f.a]).dot(
          ver(pt[f.a], pt[f.b], pt[f.c]));
      if (d <= 0) next.push_back(f);
      int ff = (d > 0) - (d < 0);
      flag[f.a][f.b]=flag[f.b][f.c]=flag[f.c][f.a]=ff;
    }
    const auto F = [&](int x, int y) {
      if (flag[x][y] > 0 && flag[y][x] <= 0)
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
