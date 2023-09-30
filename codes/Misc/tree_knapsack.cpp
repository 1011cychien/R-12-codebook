vector<int> G[N]; int dp[N][K]; pair<int,int> obj[N];
void dfs(int u, int mx) {
  for (int s : G[u]) {
    auto [w, v] = obj[s];
    if (mx < w) continue;
    for (int i = 0; i <= mx - w; i++)
      dp[s][i] = dp[u][i];
    dfs(s, mx - w);
    for (int i = w; i <= mx; i++)
      dp[u][i] = max(dp[u][i], dp[s][i - w] + v);
  }
}
