int dp[N][K]; PII obj[N];
vector<int> G[N];
void dfs(int u, int mx){
  for(int s: G[u]) {
    if(mx < obj[s].first) continue;
    for(int i=0;i<=mx-obj[s].FF;i++)
      dp[s][i] = dp[u][i];
    dfs(s, mx - obj[s].first);
    for(int i=obj[s].FF;i<=mx;i++)
      dp[u][i] = max(dp[u][i],
        dp[s][i - obj[s].FF] + obj[s].SS);
  }
}
