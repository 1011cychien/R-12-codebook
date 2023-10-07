vector<int> de_bruijn(int k, int n) {
  // return cyclic string of len k^n s.t. every string
  // of len n using k char appears as a substring.
  vector<int> aux(n + 1), res;
  auto db = [&](auto self, int t, int p) -> void {
    if (t <= n)
      for (int i = aux[t - p]; i < k; ++i, p = t)
        aux[t] = i, self(self, t + 1, p);
    else if (n % p == 0) for (int i = 1; i <= p; ++i)
      res.push_back(aux[i]);
  }; db(db, 1, 1);
  return res;
}
