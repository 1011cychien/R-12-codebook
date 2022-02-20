struct BipartiteMatching {
  vector<int> X[N];
  int fX[N], fY[N], n;
  bitset<N> vis;
  bool dfs(int x) {
    for (auto i:X[x]) {
      if (vis[i]) continue;
      vis[i] = true;
      if (fY[i]==-1 || dfs(fY[i])){
        fY[fX[x] = i] = x;
        return true;
      }
    }
    return false;
  }
  void init(int n_, int m) {
    vis.reset();
    fill(X, X + (n = n_), vector<int>());
    memset(fX, -1, sizeof(int) * n);
    memset(fY, -1, sizeof(int) * m);
  }
  void add_edge(int x, int y){
    X[x].push_back(y); }
  int solve() { // return how many pair matched
    int cnt = 0;
    for(int i=0;i<n;i++) {
      vis.reset();
      cnt += dfs(i);
    }
    return cnt;
  }
};
