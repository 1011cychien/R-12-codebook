struct S { int i, l, r; };
void solve(int n, auto &dp, auto &f) {
  deque<S> dq; dq.emplace_back(0, 1, n);
  for (int i = 1; i <= n; ++i) {
    dp[i] = f(dq.front().i, i);
    while (!dq.empty() && dq.front().r <= i)
      dq.pop_front();
    dq.front().l = i + 1;
    while (!dq.empty() &&
        f(i, dq.back().l) >= f(dq.back().i, dq.back().l))
      dq.pop_back();
    int p = i + 1;
    if (!dq.empty()) {
      auto [j, l, r] = dq.back();
      for (int s = 1 << 20; s; s >>= 1)
        if (l+s <= n && f(i, l+s) < f(j, l+s)) l += s;
      dq.back().r = l; p = l + 1;
    }
    if (p <= n) dq.emplace_back(i, p, n);
  } // dp[i] = max(dp[j] + w(j + 1, i) | j < i)
} // test @ tioj 烏龜疊疊樂
// vector<int64_t> dp(n + 1); dp[0] = 0;
// auto f = [&](int l, int r) -> int64_t {
//   if (r - l > k) return -INF;
//   return dp[l] + w(l + 1, r);
// };
