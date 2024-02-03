struct TwoSat : SCC {
  void orr(int x, int y) {
    if ((x ^ y) == 1) return;
    add_edge(x ^ 1, y); add_edge(y ^ 1, x);
  }
  vector<int> solve2sat() {
    solve(); vector<int> res(n);
    for (int i = 0; i < n; i += 2)
      if (idx[i] == idx[i + 1]) return {};
    for (int i = 0; i < n; i++)
      res[i] = idx[i] < idx[i ^ 1];
    return res;
  }
};
