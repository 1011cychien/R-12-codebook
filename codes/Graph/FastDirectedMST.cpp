using D = int64_t;
struct E { int s, t; D w; }; // 0-base
vector<int> dmst(const vector<E> &e, int n, int root) {
  using PQ = pair<min_heap<pair<D, int>>, D>;
  auto push = [](PQ &pq, pair<D, int> v) {
    pq.first.emplace(v.first - pq.second, v.second); };
  auto top = [](const PQ &pq) -> pair<D, int> {
    auto r = pq.first.top();
    return {r.first + pq.second, r.second}; };
  auto join = [&push, &top](PQ &a, PQ &b) {
    if (a.first.size() < b.first.size()) swap(a, b);
    for (; !b.first.empty(); b.first.pop())
      push(a, top(b)); };
  vector<PQ> h(n * 2);
  for (size_t i = 0; i < e.size(); ++i)
    push(h[e[i].t], {e[i].w, i});
  vector<int> a(n*2), v(n*2, -1), pa(n*2, -1), r(n*2);
  iota(a.begin(), a.end(), 0);
  auto o = [&](int x) { int y;
    for (y = x; a[y] != y; y = a[y]);
    for (int ox = x; x != y; ox = x)
      x = a[x], a[ox] = y;
    return y; };
  int pc = (v[root] = n + 1) - 1;
  for (int i = 0; i < n; ++i) if (v[i] == -1)
    for (int p=i; v[p]<0||v[p]==i; p=o(e[r[p]].s)) {
      if (int q = p; v[q] == i && (p = pc++, 1)) do {
        h[q].second = -h[q].first.top().first;
        join(h[pa[q] = a[q] = p], h[q]);
      } while ((q = o(e[r[q]].s)) != p);
      for(v[p]=i;!h[p].first.empty()&&o(e[top(h[p]).second].s)==p;h[p].first.pop());
      r[p] = top(h[p]).second;
    }
  vector<int> ans;
  for (int i=pc-1;i>=0;i--) if (i!=root&&v[i]!=n) {
    for (int f = e[r[i]].t; f!=-1&&v[f]!=n; f = pa[f])
      v[f] = n;
    ans.push_back(r[i]);
  }
  return ans; // default minimize, returns edgeid array
}
