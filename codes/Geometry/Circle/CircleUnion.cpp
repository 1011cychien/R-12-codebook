#define eb emplace_back
struct Teve { // test@SPOJ N=1000, 0.3~0.5s
  PTF p; llf a; int add; // point, ang, add
  Teve(PTF x, llf y, int z) : p(x), a(y), add(z) {}
  bool operator<(Teve &b) const { return a < b.a; }
};
// strict: x = 0, otherwise x = -1
bool disjunct(Cir &a, Cir &b, int x)
{ return sgn(abs(a.o - b.o) - a.r - b.r) > x; }
bool contain(Cir &a, Cir &b, int x)
{ return sgn(a.r - b.r - abs(a.o - b.o)) > x; }
vector<llf> CircleUnion(vector<Cir> &c) {
  // area[i] : area covered by at least i circles
  int N = (int)c.size(); vector<llf> area(N + 1);
  vector<vector<int>> overlap(N, vector<int>(N));
  auto g = overlap; // use simple 2darray to speedup
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      /* c[j] is non-strictly in c[i]. */
      overlap[i][j] = i != j &&
        (sgn(c[i].r - c[j].r) > 0 ||
         (sgn(c[i].r - c[j].r) == 0 && i < j)) &&
        contain(c[i], c[j], -1);
    }
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      g[i][j] = i != j && !(overlap[i][j] ||
          overlap[j][i] || disjunct(c[i], c[j], -1));
  for (int i = 0; i < N; ++i) {
    vector<Teve> eve; int cnt = 1;
    for (int j = 0; j < N; ++j) cnt += overlap[j][i];
    // if (cnt > 1) continue; (if only need area[1])
    for (int j = 0; j < N; ++j) if (g[i][j]) {
      auto IP = intersectPoint(c[i], c[j]);
      PTF aa = IP[1], bb = IP[0];
      llf A = arg(aa - c[i].o), B = arg(bb - c[i].o);
      eve.eb(bb, B, 1); eve.eb(aa, A, -1);
      if (B > A) ++cnt;
    }
    if (eve.empty()) area[cnt] += PI*c[i].r*c[i].r;
    else {
      sort(eve.begin(), eve.end());
      eve.eb(eve[0]); eve.back().a += PI * 2;
      for (size_t j = 0; j + 1 < eve.size(); j++) {
        cnt += eve[j].add;
        area[cnt] += cross(eve[j].p, eve[j+1].p) *.5;
        llf t = eve[j + 1].a - eve[j].a;
        area[cnt] += (t-sin(t)) * c[i].r * c[i].r *.5;
      }
    }
  }
  return area;
}
