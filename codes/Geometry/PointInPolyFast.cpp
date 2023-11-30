vector<int> PIPfast(vector<P> p, vector<P> q) {
  const int N = int(p.size()), Q = int(q.size());
  vector<pair<P, int>> evt;
  vector<Seg> edge;
  for (int i = 0; i < N; i++) {
    int a = i, b = (i + 1) % N;
    P A = p[a], B = p[b];
    assert (A < B || B < A); // std::operator<
    if (B < A) swap(A, B);
    evt.emplace_back(A, i);
    evt.emplace_back(B, ~i);
    edge.emplace_back(A, B);
  }
  for (int i = 0; i < Q; i++)
    evt.emplace_back(q[i], i + N);
  sort(all(evt));
  auto vtx = p; sort(all(vtx));
  auto eval = [](const Seg &a, lld x) -> llf {
    if (RE(a.dir) == 0) {
      assert (x == RE(a.st));
      return IM(a.st) + llf(IM(a.dir)) / 2;
    }
    llf t = (x - RE(a.st)) / llf(RE(a.dir));
    return IM(a.st) + IM(a.dir) * t;
  };
  lld cur_x = 0;
  auto cmp = [&](const Seg &a, const Seg &b) -> bool {
    if (int s = sgn(eval(a, cur_x) - eval(b, cur_x)))
      return s == -1;
    int s = sgn(cross(b.dir, a.dir));
    if (cur_x != RE(a.st) && cur_x != RE(b.st)) s *= -1;
    return s == -1;
  };
  namespace pbds = __gnu_pbds;
  using Tree = pbds::tree<Seg, int, decltype(cmp),
        pbds::rb_tree_tag,
        pbds::tree_order_statistics_node_update>;
  Tree st(cmp);
  vector<int> ans(Q);
  for (auto [ep, i] : evt) {
    cur_x = RE(ep);
    if (i < 0) { // remove
      st.erase(edge[~i]);
    } else if (i < N) { // insert
      auto [it, succ] = st.insert({edge[i], i});
      assert (succ);
    } else {
      int qid = i - N;
      if (binary_search(all(vtx), ep)) { // on vertex
        ans[qid] = 1;
        continue;
      }
      Seg H(ep, ep); // ??
      auto it = st.lower_bound(H);
      if (it != st.end() && isInter(it->first, ep)) {
        ans[qid] = 1; // on edge
        continue;
      }
      if (it != st.begin() && isInter(prev(it)->first, ep)) {
        ans[qid] = 1; // on edge
        continue;
      }
      auto rk = st.order_of_key(H);
      if (rk % 2 == 0) ans[qid] = 0; // outside
      else ans[qid] = 2; // inside
    }
  }
  return ans;
} // test @ AOJ CGL_3_C
