struct HK {
  vector<int> l, r, a, p; int ans; queue<int> q;
  HK(int n, int m, auto &g) : l(n,-1),r(m,-1),ans(0) {
    do {
      a.assign(n, -1); p = a; q = queue<int>();
      for (int i = 0; i < n; i++)
        if (l[i] == -1) q.push(a[i] = p[i] = i);
    } while (bfs(g));
  }
  bool bfs(auto &g) {
    // bitset<maxn> nvis, t; nvis.set();
    for (int z, x; !q.empty(); q.pop())
      // or use _Find_first and _Find_next here
      if (l[a[x = q.front()]] == -1) for (int y: g[x]) {
        // nvis.reset(y);
        if (r[y] == -1) {
          for (z = y; z != -1; )
            r[z] = x, swap(l[x], z), x = p[x];
          return ++ans, true;
        } else if (p[r[y]] == -1)
          q.push(z = r[y]), p[z] = x, a[z] = a[x];
      }
    return false;
  }
};
