# Matching & Flow

## HopcroftKarp
### Description

An $O(|E| \sqrt{|V|})$ bipartite matching algorithm.  
Basically a low constant Dinic's algorithm.

Number of matching saved in `ans`, and the corresponding matching saved in `l` and `r`.
~~Not sure about what `a` and `p` does.~~ `a` and `p` are auxiliary array when doing BFS.

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/164965)


## Dijkstra Cost Flow
### Description

Successive Shortest Path Algorithm using Dijkstra's algorithm.

### Test Status

Tested on [ARC122 F](https://atcoder.jp/contests/arc122/submissions/44122501) and [LibreOJ 102](https://loj.ac/s/1911311)


## Dinic
### Description
$O(V^2E)$ and $\Theta(acceptable)$ in practice.
### Test Status
Passed luogu P3376


## Flow Models
### Description
Some models. Need check.
### Test Status
TODO

## General Graph Matching
### Description

Matching in $O(|V|^3)$.
[ref-slide](https://jacky860226.github.io/general-graph-weighted-match-slides/#/22)

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/166034)


## Global Min-Cut
### Description

Stoer-Wagner algorithm solves the minimum cut problem in undirected weighted graphs with non-negative weights.  
Our code looks like an $O(N^3)$ implementation.

### Test Status

TODO


## GomoryHu Tree
### Description

For a given non-negative weighted tree, this algorithm returns a weighted tree (Gomory-Hu Tree).
For any $s$, $t$, the minimum $s$-$t$ cut in the orginal graph is equal to the minimum values among the path between $s$ and $t$ in the Gomory-Hu Tree.

Runs in $(|V|-1)\times O(\text{maflow})$.

Need to adapt current Dinic's algorithm.

Something I don't understand: In the Gomory-Hu tree, for any pair of vertices not just the size of the minimum cut between them is equal to the size of the minimum cut in the original graph (as Wikipedia claims), but also the minimum cut itself (as a partition of the vertex set into two). ([Petr's blog](https://blog.mitrichev.ch/2022/02/a-gomory-hu-week.html))

Fun Fact: Gomory-Hu Tree can be computed in almost linear time. (see [this](https://arxiv.org/abs/2111.04958))

### Test Status

Passed [CF 343E](https://codeforces.com/contest/343/submission/228226556)

## Kuhn Munkres
### Description
KM algo.
### Test Status
Passed [UOJ 80](https://uoj.ac/submission/656805) and [Library Checker](https://judge.yosupo.jp/submission/166079).


## Minimum Cost Circulation
### Description

Network simplex method. Exponential time complexity, but it runs not too slow in practice.

### Test Status

Tested on [UOJ #487](https://uoj.ac/submission/659272), [UOJ #680](https://uoj.ac/submission/659396), and [LibreOJ 102](https://loj.ac/s/1911317).  
**Cannot** pass [QOJ 7185](https://qoj.ac/contest/1356/problem/7185)


## Minimum Cost Max Flow
### Description

Successive Shortest Path Algorithm using SPFA (Bellman-Ford algorithm).

### Test Status

Passed [LibreOJ 102](https://loj.ac/s/1911310).
Testdata in LOJ is not strong in general.


## Weighted Matching
### Description

Weighted matching in $O(|V|^3)$.
[ref-slide](https://jacky860226.github.io/general-graph-weighted-match-slides/#/22)

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/166076)
