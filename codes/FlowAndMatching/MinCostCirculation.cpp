int vis[N], visc, fa[N], fae[N], head[N], mlc = 1;
struct ep {
  int to, next;
  ll flow, cost;
} e[M << 1];
void adde(int u, int v, ll fl, int cs) {
  e[++mlc] = {v, head[u], fl, cs};
  head[u] = mlc;
  e[++mlc] = {u, head[v], 0, -cs};
  head[v] = mlc;
}
void dfs(int u) {
  vis[u] = 1;
  for (int i = head[u], v; i; i = e[i].next)
    if (!vis[v = e[i].to] and e[i].flow)
      fa[v] = u, fae[v] = i, dfs(v);
}
ll phi(int x) {
  static ll pi[N];
  if (x == -1) return 0;
  if (vis[x] == visc) return pi[x];
  return vis[x] = visc, pi[x] = phi(fa[x]) - e[fae[x]].cost;
}
void pushflow(int x, ll &cost) {
  int v = e[x ^ 1].to, u = e[x].to;
  ++visc;
  while (v != -1) vis[v] = visc, v = fa[v];
  while (u != -1 && vis[u] != visc)
    vis[u] = visc, u = fa[u];
  vector<int> cyc;
  int e2 = 0, pa = 2;
  ll f = e[x].flow;
  for (int i = e[x ^ 1].to; i != u; i = fa[i]) {
    cyc.push_back(fae[i]);
    if (e[fae[i]].flow < f)
      f = e[fae[e2 = i] ^ (pa = 0)].flow;
  }
  for (int i = e[x].to; i != u; i = fa[i]) {
    cyc.push_back(fae[i] ^ 1);
    if (e[fae[i] ^ 1].flow < f)
      f = e[fae[e2 = i] ^ (pa = 1)].flow;
  }
  cyc.push_back(x);
  for (int cyc_i : cyc) {
    e[cyc_i].flow -= f, e[cyc_i ^ 1].flow += f;
    cost += 1ll * f * e[cyc_i].cost;
  }
  if (pa == 2) return;
  int le = x ^ pa, l = e[le].to, o = e[le ^ 1].to;
  while (l != e2) {
    vis[o] = 0;
    swap(le ^= 1, fae[o]), swap(l, fa[o]), swap(l, o);
  }
}
ll simplex() { // 1-based
  ll cost = 0;
  memset(fa, -1, sizeof(fa)), dfs(1);
  vis[1] = visc = 2, fa[1] = -1;
  for (int i = 2, pre = -1; i != pre; i = (i == mlc ? 2 : i + 1))
    if (e[i].flow and e[i].cost < phi(e[i ^ 1].to) - phi(e[i].to))
      pushflow(pre = i, cost);
  return cost;
}
