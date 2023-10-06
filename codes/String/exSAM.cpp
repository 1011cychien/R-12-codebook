struct exSAM {
  int len[maxn * 2], link[maxn * 2]; // maxlen, suflink
  int next[maxn * 2][maxc], tot; // [0, tot), root = 0
  int ord[maxn * 2]; // topo. order (sort by length)
  int cnt[maxn * 2]; // occurence
  int newnode() {
    fill_n(next[tot], maxc, 0);
    return len[tot] = cnt[tot] = link[tot] = 0, tot++;
  }
  void init() { tot = 0, newnode(), link[0] = -1; }
  int insertSAM(int last, int c) {
    int cur = next[last][c];
    len[cur] = len[last] + 1;
    int p = link[last];
    while (p != -1 && !next[p][c])
      next[p][c] = cur, p = link[p];
    if (p == -1) return link[cur] = 0, cur;
    int q = next[p][c];
    if (len[p] + 1 == len[q]) return link[cur] = q, cur;
    int clone = newnode();
    for (int i = 0; i < maxc; ++i)
      next[clone][i] = len[next[q][i]] ? next[q][i] : 0;
    len[clone] = len[p] + 1;
    while (p != -1 && next[p][c] == q)
      next[p][c] = clone, p = link[p];
    link[link[cur] = clone] = link[q];
    link[q] = clone;
    return cur;
  }
  void insert(const string &s) {
    int cur = 0;
    for (char ch : s) {
      int &nxt = next[cur][int(ch - 'a')];
      if (!nxt) nxt = newnode();
      cnt[cur = nxt] += 1;
    }
  }
  void build() {
    queue<int> q; q.push(0);
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (int i = 0; i < maxc; ++i)
        if (next[cur][i]) q.push(insertSAM(cur, i));
    }
    vector<int> lc(tot);
    for (int i = 1; i < tot; ++i) ++lc[len[i]];
    partial_sum(all(lc), lc.begin());
    for (int i = 1; i < tot; ++i) ord[--lc[len[i]]] = i;
  }
  void solve() {
    for (int i = tot - 2; i >= 0; --i)
      cnt[link[ord[i]]] += cnt[ord[i]];
  }
};
