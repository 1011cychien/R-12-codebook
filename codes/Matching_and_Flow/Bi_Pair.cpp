// G[x] = edges from x. O(|match| * (E+V))
int solve(vector<vector<int>> &G, int n, int m) {
  vector<int> fY(m, -1), vis(m, -1); int c = 0;
  const auto F = [&](auto self, int x) -> bool {
    for (int i : G[x]) if (chmax(vis[i], c))
      if (fY[i] == -1 || self(self, fY[i]))
        return fY[i] = x, true;
    return false;
  };
  for (int i = 0; i < n; i++) if (F(F, i)) ++c;
  return c;
}
