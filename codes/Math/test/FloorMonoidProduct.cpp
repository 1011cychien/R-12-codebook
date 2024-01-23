#include <bits/stdc++.h>
using namespace std;

using llu = uint64_t;
using u128 = __uint128_t;

struct Z {
  string s;
  Z operator*(const Z &rhs) { return {s + rhs.s}; }
};

template <typename T> T mpow(T e, llu p) {
  T r;
  while (p) {
    if (p & 1) r = r * e;
    e = e * e;
    p >>= 1;
  }
  return r;
}

template <typename T>
T brute(llu a, llu b, llu c, llu n, T U, T R) {
  T res;
  for (llu i = 1, l = 0; i <= n; i++, res = res * R)
    for (llu r = (a*i+b)/c; l < r; ++l) res = res * U;
  return res;
}

template <typename T>
T euclid(llu a, llu b, llu c, llu n, T U, T R) {
  if (!n) return T{};
  if (b >= c)
    return mpow(U, b / c) * euclid(a, b % c, c, n, U, R);
  if (a >= c)
    return euclid(a % c, b, c, n, U, mpow(U, a / c) * R);
  llu m = (u128(a) * n + b) / c;
  if (!m) return mpow(R, n);
  return mpow(R, (c - b - 1) / a) * U
    * euclid(c, (c - b - 1) % a, a, m - 1, R, U)
    * mpow(R, n - (u128(c) * m - b - 1) / a);
}
// time complexity is O(log max(a, b, c))
// UUUU R UUUUU R ... UUU R 共 N 個 R，最後一個必是 R
// 一直到第 k 個 R 前總共有 (ak+b)/c 個 U

int main() {
  Z U{"U"}, R{"R"};
  for (int a = 0; a < 10; a++)
    for (int b = 0; b < 10; b++)
      for (int c = 1; c <= 10; c++)
        for (int n = 1; n <= 10; n++) {
          auto E = euclid(a, b, c, n, U, R);
          auto B = brute(a, b, c, n, U, R);
          assert(E.s == B.s);
        }
  for (int iter = 0; iter < 10; iter++) {
    llu a, b, c, n;
    a = rand() % (10000);
    b = rand() % (10000);
    c = rand() % (10000) + 1;
    n = rand() % (10000);
    auto E = euclid(a, b, c, n, U, R);
    auto B = brute(a, b, c, n, U, R);
    assert(E.s == B.s);
  }
}
