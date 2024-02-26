void BWT(char *ori, char *res) {
  // make ori -> ori + ori then build suffix array
}
void iBWT(char *ori, char *res) {
  vector<int> v[SIGMA], a;
  const int len = strlen(ori); res[len] = 0;
  for (int i = 0; i < len; i++) v[ori[i] - 'a'].pb(i);
  for (int i = 0, ptr = 0; i < SIGMA; i++)
    for (int j : v[i]) a.pb(j), ori[ptr++] = 'a' + i;
  for (int i = 0, ptr = 0; i < len; i++)
    res[i] = ori[a[ptr]], ptr = a[ptr];
}
