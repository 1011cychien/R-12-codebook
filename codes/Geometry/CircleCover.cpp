#define eb emplace_back
struct CircleCover { // tested on SPOJ 0.56s N=1000
  struct Teve {
    PTF p; llf ang; int add;
    Teve() {}
    Teve(PTF a, llf b, int c) : p(a), ang(b), add(c) {}
    bool operator<(const Teve &a)
      const { return ang < a.ang; }
  };
  // strict: x = 0, otherwise x = -1
  bool disjunct(Cir &a, Cir &b, int x)
  { return sgn(abs(a.o - b.o) - a.r - b.r) > x; }
  bool contain(Cir &a, Cir &b, int x)
  { return sgn(a.r - b.r - abs(a.o - b.o)) > x; }
  vector<llf> solve(vector<Cir> c) {
    // area[i] : area covered by at least i circles
    int N = c.size(); vector<llf> area(N + 1);
    vector<vector<int>> overlap(N, vector<int>(N));
    auto g = overlap;
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
      for (int j = 0; j < N;++j)
        if (overlap[j][i]) ++cnt;
      // if (cnt > 1) continue; (if only need area[1])
      for (int j = 0; j < N; ++j) if (g[i][j]) {
        auto IP = intersectPoint(c[i], c[j]);
        PTF aa = IP[1], bb = IP[0];
        llf A = arg(aa - c[i].o), B = arg(bb - c[i].o);
        eve.eb(bb, B, 1); eve.eb(aa, A, -1);
        if (B > A) ++cnt;
      }
      if (eve.empty())
        area[cnt] += pi * c[i].r * c[i].r;
      else {
        sort(eve.begin(), eve.end());
        eve.eb(eve[0]); eve.back().ang += 2. * pi;
        for (size_t j = 0; j + 1 < eve.size(); j++) {
          cnt += eve[j].add;
          area[cnt] += cross(eve[j].p,eve[j+1].p)*.5;
          llf t = eve[j + 1].ang - eve[j].ang;
          area[cnt] += (t-sin(t)) *c[i].r*c[i].r *.5;
        }
      }
    }
    return area;
  }
} CCO;
