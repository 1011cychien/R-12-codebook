string mcp(string s) {
  int n = s.length();
  s += s; int i = 0, j = 1;
  while (i < n && j < n) {
    int k = 0;
    while (k < n && s[i + k] == s[j + k]) k++;
    ((s[i + k] <= s[j + k]) ? j : i) += k + 1;
    j += (i == j);
  }
  return s.substr(i < n ? i : j, n);
}
