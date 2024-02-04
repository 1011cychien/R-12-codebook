# Math

## Common bounds
### Description
Partition function, divisor function, catalan number,
bell number
### Test Status
No test.

## Equations
### Description
many equations.
- Stirling Number
- Derivatives
- Extended Euler
- Pentagonal number theorem
### Test Status
No test.

## Extended Floor Sum
### Description
A recursion formula.
### Test Status
No test.

## Integer Division
### Description
C++ integer division to normal integer division.
### Test Status
Copied from 8BQube

## Floor Sum
### Description
Calculate $\sum _ {i=0} ^ {n-1} \lfloor \frac{ai + b}{m} \rfloor$.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165193) (negative coefficient not tested).

## ModMin
### Description
Return the minimum $x \geq 0$ such that $l \leq ax \mod m \leq r$.
### Test Status
Tested on [SEERC'20 G](https://codeforces.com/gym/102411/submission/212888594)

## Floor Monoid Product
### Description
萬能歐幾里得
[ref1](https://www.cnblogs.com/apjifengc/p/17492207.html)
[ref2](https://maspypy.github.io/library/mod/floor_monoid_product.hpp)
### Test Status
https://judge.yosupo.jp/submission/185615
https://www.luogu.com.cn/record/144016921
https://loj.ac/s/1986411

## ax + by = gcd
### Description
exgcd algorithm.
### Test Status
See CRT section.

## Chinese Remainder
### Description
Solves $x \equiv r_1 \pmod {m_1}$ and $x \equiv r_2 \pmod {m_2}$.
If no solution, returns false
### Test Status
Passed luogu P4777.

## DiscreteLog
### Description
BSGS algorithm.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165189)

## Quadratic Residue
### Description
Square root under modulo prime.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/186095)

## FWT
### Description
Bitwise XOR/AND/OR convolution.
### Test Status
Passed yosupo judge, [XOR](https://judge.yosupo.jp/submission/183213) and [AND](https://judge.yosupo.jp/submission/183214) version.

## Packed FFT
### Description
`convolution` uses less times of FFT.
`convolution_mod` decompose numbers to high and low part, make FFT precision better.
reference:
- [淺談 FFT](https://www.luogu.com.cn/blog/105254/qian-tan-fft-zong-ft-dao-fft)
- [題解 P4245](https://www.luogu.com.cn/blog/command-block/solution-p4245#)

### Test Status
Passed [convolution mod](https://judge.yosupo.jp/submission/187951) with long double.
For $N = 524288$,
- normal NTT (998244353): ~230ms
- three-mod-NTT: ~430ms
- `convolution_mod` ~1000ms with long double (AC), 400ms with double (WA)
- `convolution`: ~800ms with long double (WA)

The first function passed [Because, art](https://codeforces.com/gym/103640/submission/244575267).

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

## FPS
### Description
Common Formal Power Series operations.
Exp and Pow are relatively slow at yosupo library checker.

Do we need [Consecutive Terms of Linear Recurrent Sequence](https://judge.yosupo.jp/submission/182351)?

### Test Status
[Inv](https://judge.yosupo.jp/submission/182577)
[Ln](https://judge.yosupo.jp/submission/182580)
[Exp](https://judge.yosupo.jp/submission/182581)
[Pow](https://judge.yosupo.jp/submission/182585)
[Sqrt](https://judge.yosupo.jp/submission/182589)
[Eval](https://judge.yosupo.jp/submission/182593)
[DivMod](https://judge.yosupo.jp/submission/182594)
[LinearRecursionKth](https://judge.yosupo.jp/submission/182594)

## Partition Number
### Description
Calculate first $N$ partition number in $O(N\sqrt{N})$.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165173) $N=500000$ in 557ms.

## Pi Count
### Description
Count prime in sublinear time.
<!-- TODO improve performance (or delete this?) -->
The code is copied from 8BQube and simplified.
### Test Status
<!-- Passed [yosupo judge](https://judge.yosupo.jp/submission/165124), but very slow. -->
Passed [yosupo judge](https://judge.yosupo.jp/submission/182619)

## Miller Rabin
### Description
Prime detect. Be careful about mpow and mmul.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/175688) in 1632ms ($10^5$ tests).
w/ Montgomery Multiplication runs in
[219ms](https://judge.yosupo.jp/submission/187075).

## Pollard Rho
### Description
Factorization. Be careful about mpow and mmul.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/175689) in 313ms ($100$ tests).
w/ Montgomery Multiplication runs in
[72ms](https://judge.yosupo.jp/submission/187074).

## Berlekamp Massey
### Description
BM algo.
### Test Status
Passed [yosupo judge](https://judge.yosupo.jp/submission/165366).

## Gauss Elimination
### Description
Make RREF and solve system of linear equations.
### Test status
[library checker](https://judge.yosupo.jp/submission/187171).

## Charateristic Polynomial
### Description
Calculate the charateristic polynomial of matrix in $O(N^3)$.
### Test Status
Passed 2021 PTZ Korea and [library checker](https://judge.yosupo.jp/submission/187174).

## Simplex / Simplex Construction
### Description
Linear programming.
### Test Status
Passed [Red and Black Tree](https://codeforces.com/contest/375/submission/243194774).
[long double](https://codeforces.com/contest/375/submission/243194767) runs 3 times slower.

## Adaptive Simpson
### Description
Simpson integration method.
Unknown time complexity.
### Test Status
Passed [Two Cylinders](https://codeforces.com/problemsets/acmsguru/submission/99999/244862663).

## Golden Ratio Search
### Description
Ternary search with less query number
### Test Status
TODO
copied from kactl.
