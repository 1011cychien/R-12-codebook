// from 8BQube, plz ensure p is strict convex hull
const llf INF = 1e18, qi = acos(-1) / 2 * 3;
pair<llf, llf> solve(vector<P> &p) {
#define Z(v) (p[v] - p[i])
  llf mx = 0, mn = INF;
  int n = (int)p.size(); p.emplace_back(p[0]);
  for (int i = 0, u = 1, r = 1, l = 1; i < n; ++i) {
    P e = Z(i + 1);
    while (cross(e, Z(u + 1)) > cross(e, Z(u)))
      u = (u + 1) % n;
    while (dot(e, Z(r + 1)) > dot(e, Z(r)))
      r = (r + 1) % n;
    if (!i) l = (r + 1) % n;
    while (dot(e, Z(l + 1)) < dot(e, Z(l)))
      l = (l + 1) % n;
    P D = p[r] - p[l];
    mn = min(mn, dot(e, D) / llf(norm(e)) * cross(e, Z(u)));
    llf B = sqrt(norm(D)) * sqrt(norm(Z(u)));
    llf deg = (qi - acos(dot(D, Z(u)) / B)) / 2;
    mx = max(mx, B * sin(deg) * sin(deg));
  }
  return {mn, mx};
}
