int b = sqrt(n);
ans[0] = tmp[0] = 1;
for (int i = 1; i <= b; i++) {
  for (int rep = 0; rep < 2; rep++)
    for (int j = i; j <= n - i * i; j++)
      modadd(tmp[j], tmp[j-i]);
  for (int j = i * i; j <= n; j++)
    modadd(ans[j], tmp[j - i * i]);
}
