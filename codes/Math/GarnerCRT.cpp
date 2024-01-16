const int mod = 1000000007;
const int M1 = 985661441; // G = 3 for M1, M2, M3
const int M2 = 998244353;
const int M3 = 1004535809;
int superBigCRT(lld A, lld B, lld C) {
    static_assert (M1 < M2 && M2 < M3);
    constexpr lld r12 = modpow(M1, M2-2, M2);
    constexpr lld r13 = modpow(M1, M3-2, M3);
    constexpr lld r23 = modpow(M2, M3-2, M3);
    constexpr lld M1M2 = 1LL * M1 * M2 % mod;
    B = (B - A + M2) * r12 % M2;
    C = (C - A + M3) * r13 % M3;
    C = (C - B + M3) * r23 % M3;
    return (A + B * M1 + C * M1M2) % mod;
}
