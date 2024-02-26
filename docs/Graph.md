# Graph

## SCC
### Description
Tarjan algorithm.
The constant is generally better than kosaraju.

TODO Kosaraju and bitset-optimized Kosaraju.

### Test Status
Passed [SCC](https://judge.yosupo.jp/submission/188293).

## 2-SAT
### Description
2-SAT construction.

To use 2-SAT with $n$ variables, call constructor with $2n$.
$2i$ and $2i+1$ represents $x$ and $\neg x$.
$x \lor x$ or $\neg x \lor \neg x$ is OK.

### Test Status
Passed CSES Giant Pizza and [CF Radio Stations](https://codeforces.com/contest/1215/submission/245999562).
Passed [2 SAT](https://judge.yosupo.jp/submission/188294).

## BCC
### Description
Gives AP and bridge and `bcc_id`.
`bcc_id[edge_id]` is the bcc of the edge.
### Test Status
Passed [Two-Edge-Connected-Components](https://judge.yosupo.jp/submission/182663) and [Biconnected Components](https://judge.yosupo.jp/submission/182798).
`is_ap` function is not tested.

## Round Square Tree
### Description
Or block-cut-tree. Useful tree for "simple path" queries.
There will be at most $2N$ vertices in the new tree.
### Test Status
Passed [2020 Shanghai K](https://codeforces.com/gym/102900/submission/223293046)
Passed [Biconnected Components](https://judge.yosupo.jp/submission/182668)

## Edge TCC
### Description
Edge triconnected component.
### Test Status
Passed [yosupo library checker](https://judge.yosupo.jp/submission/161793).

## Bipolar Orientation
### Description
Bipolar orientation algo
### Test Status
Passed [1916F](https://codeforces.com/contest/1916/submission/248286992).

## DMST
### Description
Directed Minimum Spanning Tree in $O(E\log ^2 E)$.
Use mergable heap instead of small-to-big for better complexity?
### Test Status
Passed [yosupo library checker](https://judge.yosupo.jp/submission/182697)
[CF 100307 D](https://codeforces.com/gym/100307/submission/241048738)

## Dominator Tree
### Description
Dominator tree in $O(E\log V)$.
The ancestor relation on the tree is the
"must-pass-from-source" relation in original graph.
### Test Status
Passed [yosupo library checker](https://judge.yosupo.jp/submission/182701).

## Edge Coloring
### Description
[Misra & Gries edge coloring algorithm](https://en.wikipedia.org/wiki/Misra_%26_Gries_edge_coloring_algorithm).
Runs in $O(NM)$
### Test Status
Passed [NCPC 2018 G](https://codeforces.com/gym/101933/submission/233996239).

## Centroid Decomp.
### Description
Mark a vertex or query the sum of distance from a vertex to
all marked vertices.

Need rewrite or smt?
### Test Status
Passed [TIOJ 1171](https://tioj.ck.tp.edu.tw/submissions/370410).

## Lowbit Decomp.
### Description
Some chain decomposition of tree.
### Test Status
Passed [Vertex Add Path Sum](https://judge.yosupo.jp/submission/193555).

## Virtual Tree
### Description
Dependency: `lca`.
Gives the critital nodes of given subset.
Always include the original root.
The edges are given in rooted tree format.
### Test Status
Used in contest. TODO.

## Tree Hashing
### Description
Some PRNG random hash.
### Test Status
Passed [UOJ 763](https://uoj.ac/submission/672367) and [library checker](https://judge.yosupo.jp/submission/182721).
Passed [QOJ 499](https://qoj.ac/submission/327465).

## Mo's Algo on Tree
### Description
Pseudo code of mo's algo on tree.
`push` means XOR the contribution.
### Test Status
TODO

## Count Cycles
### Description
Count 3-cycle and 4-cycle in $O(M\sqrt{M})$.
### Test Status
Passed [CCPC Guangzhou](https://codeforces.com/gym/104053/problem/K).

## Maximal Clique
### Description
Enumerate maximal clique.
Time complexity $O(n3^{n/3})$ or $O(nC)$ where $C$
is the number of such cliques.
### Test Status
Can run on $n=80$ on [TIOJ](https://tioj.ck.tp.edu.tw/submissions/357847).
[library checker enumerate cliques](https://judge.yosupo.jp/submission/193392)

## Maximum Clique
### Description
MaxCliqueDyn algo
Get maximum clique with ?? time complexity.
### Test Status
kactl says it can run on $n=155$.
For $n=100$ on POJ, runs in 32ms.
Passed [library checker](https://judge.yosupo.jp/submission/165918).

## Min Mean Cycle
### Description
$O(V(V+E))$ find min mean cycle.
Too rare to use so needs shorten.
### Test Status
Passed a UVa problem with $n=50$.
