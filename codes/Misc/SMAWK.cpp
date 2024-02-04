// For all 2x2 submatrix:
// If M[1][0] < M[1][1], M[0][0] < M[0][1]
// If M[1][0] == M[1][1], M[0][0] <= M[0][1]
// M[i][ans_i] is the best value in the i-th row
VI smawk(int N, int M, auto &&select) {
  auto solve = [&](const VI &r, const VI &c) {
    if (r.empty()) return {};
    const int n = (int)r.size(); vector<int> c2;
    for (int i : c) {
      while (!c2.empty() && select(r[c2.size() - 1], c2.back(), i))
        c2.pop_back();
      if (c2.size() < n) c2.push_back(i);
    }
    vector<int> r2;
    for (int i = 1; i < n; i += 2) r2.push_back(r[i]);
    const auto a2 = solve(r2, c2);
    vector<int> ans(n);
    for (size_t i = 0; i < a2.size(); i++)
      ans[i * 2 + 1] = a2[i];
    for (int i = 0, j = 0; i < n; i += 2) {
      ans[i] = c2[j];
      const int end = i + 1 == n ? c2.back() : ans[i + 1];
      while (c2[j] != end) {
        j++;
        if (select(r[i], ans[i], c2[j])) ans[i] = c2[j];
      }
    }
    return ans;
  };
  vector<int> row(N), col(M);
  iota(all(row), 0), iota(all(col), 0);
  return dc(dc, row, col);
}
// if f(r, v) is better than f(r, v), return true
bool min_plus_conv_select(int r, int u, int v) {
  auto f = [](int i, int j) {
    if (0 <= i - j && i - j < n) return b[j] + a[i - j];
    return 2100000000 + (i - j);
  };
  return f(r, u) > f(r, v);
}
