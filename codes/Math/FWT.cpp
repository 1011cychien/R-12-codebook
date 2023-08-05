/* or convolution:
 * x = (x0, x0+x1), inv = (x0, x1-x0) w/o final div
 * and convolution:
 * x = (x0+x1, x1), inv = (x0-x1, x1) w/o final div */
void fwt(int x[], int N, bool inv = false) {
  for (int d = 1; d < N; d <<= 1)
    for (int s = 0; s < N; s += d * 2)
      for (int i = s; i < s + d; i++) {
        int j = i + d, ta = x[i], tb = x[j];
        x[i] = modadd(ta, tb);
        x[j] = modsub(ta, tb);
      }
  if (inv) {
    const int invn = modinv(N);
    for (int i = 0; i < N; i++)
      x[i] = modmul(x[i], invn);
  }
}
