void gauss(vector<vector<llf>> &d) {
  int n = d.size(), m = d[0].size();
  for (int i = 0; i < m; ++i) {
    int p = -1;
    for (int j = i; j < n; ++j)
      if (abs(d[j][i]) > eps)
        if (p == -1 || abs(d[j][i]) > abs(d[p][i]))
          p = j;
    if (p == -1) continue;
    for (int j = 0; j < m; ++j) swap(d[p][j], d[i][j]);
    for (int j = 0; j < n; ++j) if (j != i) {
      llf z = d[j][i] / d[i][i];
      for (int k = 0; k < m; ++k)
        d[j][k] -= z * d[i][k];
    }
  }
}
