# Math

## Common bounds
### Description
Partition function, divisor function and catalan number.
### Test Status
No test.

## Stirling Number
### Description
Stirling number formula.
Do we need this?
### Test Status
No test.

## ax + by = gcd
### Description
exgcd algorithm.
### Test Status
See CRT section.

## Chinese Remainder
### Description
Solves $x \equiv r_1 \pmod m_1$ and $x \equiv r_2 \pmod m_2$.
If no solution, returns false
### Test Status
Passed luogu P4777.

## DiscreteLog
### Description
BSGS algorithm.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165189)

## Quadratic residue
### Description
Square root under modulo prime.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/161095)

## Extended Euler
### Description
A formula.
### Test Status
No test.

## Extended Floor Sum
### Description
A recursion formula.
### Test Status
No test.

## Floor Sum
### Description
Calculate $sum_{i=0}^{n-1} floor((ai + b)/m)$.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165193) (negative coefficient not tested).

## ModMin
### Description
Return the minimum $x \geq 0$ such that $l \leq ax \mod m \leq r$.
### Test Status
Tested on [SEERC'20 G](https://codeforces.com/gym/102411/submission/212888594)

## Packed FFT
### Description
Make FFT precision better.
reference:
- [浅谈FFT](https://www.luogu.com.cn/blog/105254/qian-tan-fft-zong-ft-dao-fft)
- [题解 P4245](https://www.luogu.com.cn/blog/command-block/solution-p4245#)

### Test Status
Passed [convolution mod](https://judge.yosupo.jp/submission/166003) with long double.
For $N = 524288$,
- normal NTT (998244353): ~230ms
- three-mod-NTT: ~430ms
- `convolution_mod` ~1000ms with long double (AC), 400ms with double (WA)
- `convolution`: ~800ms with long double (WA)

## CRT for arbitrary mod
### Description
CRT for three-mod-NTT.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165178).

## NTT
### Description
NTT.
Can be modified to FFT easily.
### Test Status
Passed yosupo judge. See also "CRT for arbitrary mod".

## FWT
### Description
Bitwise XOR/AND/OR convolution.
### Test Status
Passed yosupo judge, [XOR](https://judge.yosupo.jp/submission/165179) and [AND](https://judge.yosupo.jp/submission/165183) version.

## Partition Number
### Description
Calculate first $N$ partition number in $O(N\sqrt{N})$.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165173) $N=500000$ in 557ms.

## Pi Count (+Linear Sieve)
### Description
Count prime in sublinear time.
TODO improve performance (or delete this?)
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165124), but very slow.

## Miller Rabin
### Description
Prime detect. Be careful about mpow and mmul.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/166708).

## Pollard Rho
### Description
Factorization. Be careful about mpow and mmul.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/166714).

## Berlekamp Massey
### Description
BM algo.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165366).

## Charateristic Polynomial
### Description
Calculate the charateristic polynomial of matrix in $O(N^3)$.
### Test Status
Passed 2021 PTZ Korea and yosupo library checker.

## Polynomial Operations
### Description
### Test Status
TODO.

## Simplex / Simplex Construction
### Description
Linear programming.
### Test Status
TODO.

## Adaptive Simpson
### Description
Simpson integration method.
Unknown time complexity.
### Test Status
Passed [Two Cylinders](https://codeforces.com/problemsets/acmsguru/submission/99999/227216042)
