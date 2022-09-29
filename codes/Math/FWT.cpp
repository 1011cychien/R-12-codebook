/* or convolution:
 * x = (x0, x0+x1), inv = (x0, x1-x0) w/o final div
 * and convolution:
 * x = (x0+x1, x1), inv = (x0-x1, x1) w/o final div */
void fwt(int x[], int N, bool inv = false) {
	for (int d = 1; d < N; d <<= 1) {
		for (int s = 0, d2 = d * 2; s < N; s += d2)
			for (int i = s, j = s + d; i < s + d; i++, j++) {
				int ta = x[i], tb = x[j];
				x[i] = modadd(ta, tb);
				x[j] = modsub(ta, tb);
			}
	}
	if (inv) for (int i = 0, invn = modinv(N); i < N; i++)
		x[i] = modmul(x[i], invn);
}
