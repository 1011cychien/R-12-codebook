void all_lcs(string S, string T) { // 0-base
  vector<size_t> h(T.size()); iota(all(h), 1);
  for (size_t a = 0; a < S.size(); ++a) {
    for (size_t c = 0, v = 0; c < T.size(); ++c)
      if (S[a] == T[c] || h[c] < v) swap(h[c], v);
    // here, LCS(s[0, a], t[b, c]) =
    // c - b + 1 - sum([h[i] > b] | i <= c)
  }
} // test @ yosupo judge
