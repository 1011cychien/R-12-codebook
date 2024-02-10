#define rep(i, r) for (int i = 0; i < r; i++)
struct NimProd {
  llu bit_prod[64][64]{}, prod[8][8][256][256]{};
  NimProd() {
    rep(i, 64) rep(j, 64) if (i & j) {
      int a = lowbit(i & j);
      bit_prod[i][j] = bit_prod[i ^ a][j] ^
        bit_prod[(i ^ a) | (a-1)][(j ^ a) | (i & (a-1))];
    } else bit_prod[i][j] = 1ULL << (i | j);
    rep(e, 8) rep(f, 8) rep(x, 256) rep(y, 256)
      rep(i, 8) if (x >> i & 1) rep(j, 8) if (y >> j & 1)
        prod[e][f][x][y] ^= bit_prod[e * 8 + i][f * 8 + j];
  }
  llu operator()(llu a, llu b) const {
    llu r = 0;
    rep(e, 8) rep(f, 8)
      r ^= prod[e][f][a >> (e*8) & 255][b >> (f*8) & 255];
    return r;
  }
};
