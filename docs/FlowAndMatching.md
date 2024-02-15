# Matching & Flow

## HopcroftKarp
### Description
An $O(|E| \sqrt{|V|})$ bipartite matching algorithm.
Basically a low constant Dinic's algorithm.

Number of matching saved in `ans`, and the corresponding matching saved in `l` and `r`.
~~Not sure about what `a` and `p` does.~~ `a` and `p` are auxiliary array when doing BFS.
### Test Status
Tested on [Library Checker](https://judge.yosupo.jp/submission/175638)

## Kuhn Munkres
### Description
KM algo.
### Test Status
Passed [UOJ 80](https://uoj.ac/submission/656805) and [Library Checker](https://judge.yosupo.jp/submission/166079).

## Flow Models
### Description
Some models. Need check.
### Test Status
TODO

## Dinic
### Description
Dinic with capacity scaling.
See [this](https://codeforces.com/blog/entry/52714) and [this](https://codeforces.com/blog/entry/66006).
$O(VE \log U)$ and $\Theta(acceptable)$ in practice.
### Test Status
Passed [luogu P3376](https://www.luogu.com.cn/record/142472662).
Passed [VN-SPOJ FFLOW](https://vn.spoj.com/files/src/32616710/).
[Without scaling](https://vn.spoj.com/files/src/32616719/) won't pass.

## HLPP
### Description
HLPP algo with gap heuristics.

Theoritical complexity is $O(V^2\sqrt{E})$.
But heuristic is powerful!

Note: Lowest Label Push Relabel is $O(\sqrt{V}E)$ on bipartie matching graph.
### Test Status
[LOJ 127](https://loj.ac/s/1978510) and [library checker bipartite matching](https://judge.yosupo.jp/submission/183404).
Passed [Matching on Bipartite Graph](https://judge.yosupo.jp/submission/183348).

Passed [VN-SPOJ FFLOW](https://vn.spoj.com/files/src/32616750/).

## Global Min-Cut
### Description
Stoer-Wagner algorithm solves the minimum cut problem in undirected weighted graphs with non-negative weights.
Our code looks like an $O(N^3)$ implementation.
### Test Status
Passed [luogu](https://www.luogu.com.cn/record/142731652)
Didn't find a $O(VE + V^2\log V)$ version.

## GomoryHu Tree
### Description
For a given non-negative weighted tree, this algorithm returns a weighted tree (Gomory-Hu Tree).
For any $s$, $t$, the minimum $s$-$t$ cut in the original graph is equal to the minimum values among the path between $s$ and $t$ in the Gomory-Hu Tree.

Runs in $(|V|-1)\times O(\text{maflow})$.

Need to adapt current Dinic's algorithm.

Something I don't understand: In the Gomory-Hu tree, for any pair of vertices not just the size of the minimum cut between them is equal to the size of the minimum cut in the original graph (as Wikipedia claims), but also the minimum cut itself (as a partition of the vertex set into two). ([Petr's blog](https://blog.mitrichev.ch/2022/02/a-gomory-hu-week.html))

Fun Fact: Gomory-Hu Tree can be computed in almost linear time. (see [this](https://arxiv.org/abs/2111.04958))
### Test Status
Passed [CF 343E](https://codeforces.com/contest/343/submission/241516652).

## MCMF
### Description
Successive Shortest Path Algorithm using SPFA (Bellman-Ford algorithm).
### Test Status
Passed [LibreOJ 102](https://loj.ac/s/1987934).
Testdata in LOJ is not strong in general.

Passed [atcoder lib contest](https://atcoder.jp/contests/practice2/submissions/50243310).
[QOJ 602](https://qoj.ac/submission/327474) (random testcase).

## Dijkstra Cost Flow
### Description
Successive Shortest Path Algorithm using Dijkstra's algorithm.
### Test Status
Tested on [ARC122 F](https://atcoder.jp/contests/arc122/submissions/49632535) and [LibreOJ 102](https://loj.ac/s/1987935)

Passed [atcoder lib contest](https://atcoder.jp/contests/practice2/submissions/50243410). (??)

## Min Cost Circulation
### Description
Network simplex method. Exponential time complexity, but it runs not too slow in practice.
### Test Status
Tested on [UOJ #487](https://uoj.ac/submission/659272), [UOJ #680](https://uoj.ac/submission/659396), and [LibreOJ 102](https://loj.ac/s/1911317).
[min_cost_b_flow](https://judge.yosupo.jp/submission/183609).
[QOJ 602](https://qoj.ac/submission/327476) (random testcase).
**Cannot** pass [QOJ 7185](https://qoj.ac/contest/1356/problem/7185)

## Capacity Scaling
### Description
### Test Status
[min_cost_b_flow](https://judge.yosupo.jp/submission/183528)
[QOJ 602](https://qoj.ac/submission/327487) (random testcase).

## General Matching
### Description
Matching in $O(|V|^3)$.
[ref-slide](https://jacky860226.github.io/general-graph-weighted-match-slides/#/22)
### Test Status
Tested on [Library Checker](https://judge.yosupo.jp/submission/182801).

## Weighted Matching
### Description
Weighted matching in $O(|V|^3)$.
[ref-slide](https://jacky860226.github.io/general-graph-weighted-match-slides/#/22)
### Test Status
Tested on [Library Checker](https://judge.yosupo.jp/submission/166076)
Passed [UOJ #81](https://uoj.ac/submission/678333).
