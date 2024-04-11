struct HK {
  vector<int> l, r, d, p; int ans;
  HK(int n, int m, auto &g) : l(n,-1), r(m,-1), ans(0) {
    while (true) {
      queue<int> q; d.assign(n, -1);
      for (int i = 0; i < n; i++)
        if (l[i] == -1) q.push(i), d[i] = 0;
      while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : g[x])
          if (r[y] != -1 && d[r[y]] == -1)
            d[r[y]] = d[x] + 1, q.push(r[y]);
      }
      bool match = false;
      for (int i = 0; i < n; i++)
        if (l[i] == -1 && dfs(g, i)) ++ans, match = true;
      if (!match) break;
    }
  }
  bool dfs(const auto &g, int x) {
    for (int y : g[x]) if (r[y] == -1 ||
        (d[r[y]] == d[x] + 1 && dfs(g, r[y])))
        return l[x] = y, r[y] = x, d[x] = -1, true;
    return d[x] = -1, false;
  }
};
