int N, M, cnt;
vector<int> G[maxn], T[maxn * 2];
int dfn[maxn], low[maxn], dfc;
int stk[maxn], tp;
void Tarjan(int u) {
  low[u] = dfn[u] = ++dfc;
  stk[++tp] = u;
  for (int v : G[u]) {
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = min(low[u], low[v]);
      if (low[v] == dfn[u]) {
        ++cnt;
        for (int x = 0; x != v; --tp) {
          x = stk[tp];
          T[cnt].push_back(x);
          T[x].push_back(cnt);
        }
        T[cnt].push_back(u);
        T[u].push_back(cnt);
      }
    } else low[u] = min(low[u], dfn[v]);
  }
}
int solve() { // remember initialize G, T, dfn, low
  cnt = N; dfc = tp = 0;
  for (int u = 1; u <= N; ++u)
    if (!dfn[u]) Tarjan(u), --tp;
}
