struct OfflineGetRange : Suffix {
  vector<vector<pair<int,int>>> qs; int qid;
  OfflineGetRange(const auto &s)
    : Suffix(s), qs(n), qid(0) {}
  int offline_get_range(int x, int len) {
    return qs[len].emplace_back(rev[x], qid), qid++;
  }
  vector<pair<int,int>> solve_get_range() {
    vector<pair<int,int>> ans(qid); Dsu dsu(n);
    for (int i = 1; i < n; i++) qs[hi[i]].eb(i, -1);
    for (int i = n - 1; i >= 0; i--)
      for (auto [pos, id] : qs[i] | views::reverse)
        if (id == -1) dsu.join(pos - 1, pos);
        else ans[id] =
            {dsu.get_min(pos), dsu.get_max(pos) + 1};
    return qs.assign(n), qid = 0, ans;
  }
};
template <int LG = 20> struct SparseTableSA : Suffix {
  array<vector<int>, LG> mn;
  SparseTableSA(const auto &s) : Suffix(s), mn{hi} {
    for (int l = 0; l + 1 < LG; l++) { mn[l + 1].resize(n);
      for (int i = 0, len = 1 << l; i + len < n; i++)
        mn[l + 1][i] = min(mn[l][i], mn[l][i + len]);
    }
  }
  int lcp(int a, int b) {
    if (a == b) return n - a;
    a = rev[a] + 1, b = rev[b] + 1;
    if (a > b) swap(a, b);
    const int lg = __lg(b - a);
    return min(mn[lg][a], mn[lg][b - (1 << lg)]);
  }
  int get_range(int x, int len) { // WIP
    int a = rev[x] + 1, b = rev[x] + 1;
    for (int l = LG - 1; l >= 0; l--) {
      const int s = 1 << l;
      if (a + s < n && mn[l][a + s] >= len) a += s;
      if (b - s >= 0 && mn[l][b - s] >= len) b -= s;
    }
    return {b - 1, a};
  }
};
