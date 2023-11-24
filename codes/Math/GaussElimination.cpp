void gauss(vector<vector<llf>> A, vector<llf> b) {
  const int n = A.size(), m = A[0].size();
  for (int i = 0; i < m; ++i) {
    int p = -1;
    for (int j = i; j < n; ++j)
      if (abs(A[j][i]) > eps)
        if (p == -1 || abs(A[j][i]) > abs(A[p][i]))
          p = j;
    if (p == -1) continue;
    swap(A[p], A[i]);
    swap(b[p], b[i]);
    for (int j = 0; j < n; ++j) if (j != i) {
      llf z = A[j][i] / A[i][i];
      for (int k = 0; k < m; ++k)
        A[j][k] -= z * A[i][k];
      b[j] -= z * b[i];
    }
  }
}
