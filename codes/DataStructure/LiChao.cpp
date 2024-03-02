// cmp(l, r, i) := is l better than r at i?
template <typename L, typename Cmp> class LiChao {
  int n; vector<L> T; Cmp cmp;
  void insert(int l, int r, int o, L ln) {
    // if (ln is empty line) return; // constant
    int m = (l + r) >> 1;
    bool atL = cmp(ln, T[o], l);
    if (cmp(ln, T[o], m)) atL ^= 1, swap(T[o], ln);
    if (r - l == 1) return;
    if (atL) insert(l, m, o << 1, ln);
    else insert(m, r, o << 1 | 1, ln);
  }
  L query(int x, int l, int r, int o) {
    if (r - l == 1) return T[o];
    int m = (l + r) >> 1;
    L s = (x < m ? query(x, l, m, o << 1)
        : query(x, m, r, o << 1 | 1));
    return cmp(s, T[o], x) ? s : T[o];
  }
public:
  LiChao(int n_, L init, Cmp &&c) : n(n_), T(n * 4, init), cmp(c) {}
  void insert(L ln) { insert(0, n, 1, ln); }
  L query(int x) { return query(x, 0, n, 1); }
};
// struct Line { lld a, b; };
// LiChao lct(
//   int(xs.size()), Line{0, INF},
//   [&u](const Line &l, const Line &r, int i) {
//     lld x = xs[i];
//     return l.a * x + l.b < r.a * x + r.b;
//   });
