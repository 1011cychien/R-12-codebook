vector<int> v[SIGMA];
void BWT(char *ori, char *res) {
  // make ori -> ori + ori
  // then build suffix array
}
void iBWT(char *ori, char *res) {
  for (int i = 0; i < SIGMA; i++) v[i].clear();
  const int len = strlen(ori);
  for (int i = 0; i < len; i++)
    v[ori[i] - 'a'].push_back(i);
  vector<int> a;
  for (int i = 0, ptr = 0; i < SIGMA; i++)
    for (int j : v[i]) {
      a.push_back(j);
      ori[ptr++] = 'a' + i;
    }
  for (int i = 0, ptr = 0; i < len; i++) {
    res[i] = ori[a[ptr]];
    ptr = a[ptr];
  }
  res[len] = 0;
}
