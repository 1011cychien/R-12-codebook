vector<int> kmp(const string &s) {
  vector<int> f(s.size(), 0);
  for (int i = 1, k = 0; i < (int)s.size(); ++i) {
    while (k > 0 && s[i] != s[k]) k = f[k - 1];
    f[i] = (k += (s[i] == s[k]));
  }
  return f;
}
vector<int> search(const string &s, const string &t) {
  // return 0-indexed occurrence of t in s
  vector<int> f = kmp(t), r;
  for (int i = 0, k = 0; i < (int)s.size(); ++i) {
    while(k > 0 && (k==(int)t.size() || s[i]!=t[k]))
      k = f[k - 1];
    k += (s[i] == t[k]);
    if (k == (int)t.size()) r.push_back(i-t.size()+1);
  }
  return res;
}
