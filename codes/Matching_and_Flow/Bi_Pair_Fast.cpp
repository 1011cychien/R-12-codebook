struct HK {
  vector<int> l, r, a, p; int ans;
  HK(int n, int m, auto &g) : l(n,-1),r(m,-1),ans(0) {
    for (bool match = true; match; ) {
      match = false; a.assign(n, -1); p = a;
      queue<int> q; int z;
      for (int i = 0; i < n; i++)
        if (l[i] == -1) q.push(a[i] = p[i] = i);
      // bitset<maxn> nvis, t; nvis.set();
      while (!q.empty()) {
        int x = q.front(); q.pop();
        if (l[a[x]] != -1) continue;
        // or use _Find_first and _Find_next here
        for (int y: g[x]) {
          // nvis.reset(y);
          if (r[y] == -1) {
            while (y != -1)
              r[y] = x, swap(l[x], y), x = p[x];
            match = true; ans++; break;
          } else if (p[r[y]] == -1)
            q.push(z = r[y]), p[z] = x, a[z] = a[x];
        }
      }
    }
  }
};
