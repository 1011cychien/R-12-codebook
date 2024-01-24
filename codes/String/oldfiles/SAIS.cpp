namespace sfx {
bool _t[maxn * 2];
int hi[maxn], rev[maxn];
int _s[maxn * 2], sa[maxn * 2], _c[maxn * 2];
int x[maxn], _p[maxn], _q[maxn * 2];
// sa[i]: sa[i]-th suffix is the
// i-th lexigraphically smallest suffix.
// hi[i]: longest common prefix
// of suffix sa[i] and suffix sa[i - 1].
void pre(int *a, int *c, int n, int z) {
  memset(a, 0, sizeof(int) * n);
  memcpy(x, c, sizeof(int) * z);
}
void induce(int *a, int *c, int *s,
    bool *t, int n, int z) {
  memcpy(x + 1, c, sizeof(int) * (z - 1));
  for (int i = 0; i < n; ++i)
    if (a[i] && !t[a[i] - 1])
      a[x[s[a[i] - 1]]++] = a[i] - 1;
  memcpy(x, c, sizeof(int) * z);
  for (int i = n - 1; i >= 0; --i)
    if (a[i] && t[a[i] - 1])
      a[--x[s[a[i] - 1]]] = a[i] - 1;
}
void sais(int *s, int *a, int *p, int *q,
 bool *t, int *c, int n, int z) {
  bool uniq = t[n - 1] = true;
  int nn=0, nz=-1, *nsa = a+n, *ns=s+n, last=-1;
  memset(c, 0, sizeof(int) * z);
  for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
  for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
  if (uniq) {
    for (int i = 0; i < n; ++i) a[--c[s[i]]] = i;
    return;
  }
  for (int i = n - 2; i >= 0; --i)
    t[i] = (s[i]==s[i + 1] ? t[i + 1] : s[i]<s[i + 1]);
  pre(a, c, n, z);
  for (int i = 1; i <= n - 1; ++i)
    if (t[i] && !t[i - 1])
      a[--x[s[i]]] = p[q[i] = nn++] = i;
  induce(a, c, s, t, n, z);
  for (int i = 0; i < n; ++i)
    if (a[i] && t[a[i]] && !t[a[i] - 1]) {
      bool neq = last < 0 || memcmp(s + a[i], s + last,
        (p[q[a[i]] + 1] - a[i]) * sizeof(int));
      ns[q[last = a[i]]] = nz += neq;
    }
  sais(ns, nsa, p+nn, q+n, t+n, c+z, nn, nz+1);
  pre(a, c, n, z);
  for (int i = nn - 1; i >= 0; --i)
    a[--x[s[p[nsa[i]]]]] = p[nsa[i]];
  induce(a, c, s, t, n, z);
}
void build(const string &s) {
  const int n = int(s.size());
  for (int i = 0; i < n; ++i) _s[i] = s[i];
  _s[n] = 0; // s shouldn't contain 0
  sais(_s, sa, _p, _q, _t, _c, n + 1, 256);
  for(int i = 0; i < n; ++i) rev[sa[i] = sa[i+1]] = i;
  int ind = hi[0] = 0;
  for (int i = 0; i < n; ++i) {
    if (!rev[i]) { ind = 0; continue; }
    while (i + ind < n &&
        s[i + ind] == s[sa[rev[i] - 1] + ind]) ++ind;
    hi[rev[i]] = ind ? ind-- : 0;
  }
}}
