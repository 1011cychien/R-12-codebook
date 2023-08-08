// G[x] = edges from x. O(V(E+V))
int solve(vector<vector<int>> &G, int n, int m) {
  vector<int> fX(n, -1), fY(m, -1), vis; int c = 0;
  const auto dfs = [&](auto self, int x) -> bool {
    for (int i : G[x]) if (not vis[i]) {
      vis[i] = true;
      if (fY[i] == -1 || self(self, fY[i]))
        return fY[fX[x] = i] = x, true;
    }
    return false;
  };
  for (int i=0; i<n; i++) vis.assign(m,0), c+=dfs(i);
  return c;
}
