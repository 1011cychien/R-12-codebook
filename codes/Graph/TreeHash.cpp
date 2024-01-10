vector<int> g[maxn]; llu h[maxn];
llu F(llu z) { // xorshift64star from iwiwi
  z ^= z >> 12; z ^= z << 25; z ^= z >> 27;
  return z * 2685821657736338717LL;
}
llu hsah(int u, int f) {
  llu r = 127; // bigger?
  for (int v : g[u]) if (v != f) r += hsah(v, u);
  return h[u] = F(r);
} // test @ UOJ 763 & yosupo library checker
