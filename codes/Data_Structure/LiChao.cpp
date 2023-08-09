struct L {
  int m, k, id;
  L() : id(-1) {}
  L(int a, int b, int c) : m(a), k(b), id(c) {}
  int at(int x) { return m * x + k; }
};
class LiChao {
private:
  int n; vector<L> nodes;
  static int lc(int x) { return 2 * x + 1; }
  static int rc(int x) { return 2 * x + 2; }
  void insert(int l, int r, int id, L ln) {
    int m = (l + r) >> 1;
    if (nodes[id].id == -1)
      return nodes[id] = ln, void();
    bool atLeft = nodes[id].at(l) < ln.at(l);
    if (nodes[id].at(m) < ln.at(m))
      atLeft ^= 1, swap(nodes[id], ln);
    if (r - l == 1) return;
    if (atLeft) insert(l, m, lc(id), ln);
    else insert(m, r, rc(id), ln);
  }
  int query(int l, int r, int id, int x) {
    int m = (l + r) >> 1, ret = 0;
    if (nodes[id].id != -1) ret = nodes[id].at(x);
    if (r - l == 1) return ret;
    if (x < m) return max(ret, query(l, m, lc(id), x));
    return max(ret, query(m, r, rc(id), x));
  }
public:
  LiChao(int n_) : n(n_), nodes(n * 4) {}
  void insert(L ln) { insert(0, n, 0, ln); }
  int query(int x) { return query(0, n, 0, x); }
};
