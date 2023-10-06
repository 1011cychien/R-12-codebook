// from 8BQube, plz ensure p is strict convex hull
const llf INF = 1e18, qi = acos(-1) / 2 * 3;
pair<llf, llf> solve(const vector<P> &p) {
  llf mx = 0, mn = INF; int n = (int)p.size();
  for (int i = 0, u = 1, r = 1, l = 1; i < n; ++i) {
#define Z(v) (p[(v) % n] - p[i])
    P e = Z(i + 1);
    while (cross(e, Z(u + 1)) > cross(e, Z(u))) ++u;
    while (dot(e, Z(r + 1)) > dot(e, Z(r))) ++r;
    if (!i) l = r + 1;
    while (dot(e, Z(l + 1)) < dot(e, Z(l))) ++l;
    P D = p[r % n] - p[l % n];
    llf H = cross(e, Z(u)) / llf(norm(e));
    mn = min(mn, dot(e, D) * H);
    llf B = sqrt(norm(D)) * sqrt(norm(Z(u)));
    llf deg = (qi - acos(dot(D, Z(u)) / B)) / 2;
    mx = max(mx, B * sin(deg) * sin(deg));
  }
  return {mn, mx};
} // test @ UVA 819
