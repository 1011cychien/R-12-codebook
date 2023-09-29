llu F(llu z) { // xorshift64 from iwiwi
  z ^= z >> 12; z ^= z << 25; z ^= z >> 27;
  return z * 2685821657736338717LL;
}
llu hsah(int u, int f) {
  llu r = 127; // bigger?
  for (int v : G[u]) if (v != f) r += F( hsah(v, u) );
  return F(r);
} // test @ UOJ 763
