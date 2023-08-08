#define rep(x, y, z) for (int x=y; x<z; x++)
using VI = vector<int>; using VVI = vector<VI>;
void Hessenberg(VVI &H, int N) {
  for (int i = 0; i < N - 2; ++i) {
    if (!H[i + 1][i])
      for (int j = i + 2; j < N; ++j) if (H[j][i]) {
        rep(k, i, N) swap(H[i+1][k], H[j][k]);
        rep(k, 0, N) swap(H[k][i+1], H[k][j]);
        break;
      }
    if (!H[i + 1][i]) continue;
    int val = modinv(H[i + 1][i]);
    for (int j = i + 2; j < N; ++j) {
      int co = mul(val, H[j][i]);
      rep(k, i, N) subeq(H[j][k], mul(H[i+1][k], co));
      rep(k, 0, N) addeq(H[k][i+1], mul(H[k][j], co));
    }
  }
}
VI CharacteristicPoly(VVI &A) {
  int N = A.size(); Hessenberg(A, N);
  VVI P(N + 1, VI(N + 1)); P[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    P[i][0] = 0;
    for (int j = 1; j <= i; ++j) P[i][j] = P[i-1][j-1];
    for (int j = i - 1, val = 1; j >= 0; --j) {
      int co = mul(val, H[j][i - 1]);
      rep(k, 0, j+1) subeq(P[i][k], mul(P[j][k], co));
      if (j) val = mul(val, H[j][j - 1]);
    }
  }
  if (N & 1) for (int &pi: P[N]) pi = sub(0, pi);
  return P[N]; // test: 2021 PTZ korea K
}
