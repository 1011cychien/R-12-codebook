# Matching & Flow

## HopcroftKarp
### Description

An $O(|E| \sqrt{|V|})$ bipartite matching algorithm.  
Basically a low constant Dinic's algorithm.

Number of matching saved in `ans`, and the corresponding matching saved in `l` and `r`.
Not sure about what `a` and `p` does.

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/164965)


## Dijkstra Cost Flow
### Description

Successive Shortest Path Algorithm using Dijkstra's algorithm.

### Test Status

Tested on [ARC122 F](https://atcoder.jp/contests/arc122/submissions/44122501)


## Dinic
### Description
### Test Status


## Flow Models
### Description
### Test Status


## General Graph Matching
### Description

Blossom Algorithm runs in $O(EV^2)$. Not sure about the complexity of ours.  
Can solve $|V|=500$ testcases though.

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/69588)


## Global Min-Cut
### Description
### Test Status


## GomoryHu Tree
### Description
### Test Status


## Kuhn Munkres
### Description
### Test Status


## Minimum Cost Circulation
### Description

Network simplex method. Exponential time complexity, but it runs not too slow in practice.

### Test Status

Tested on [UOJ #487](https://uoj.ac/submission/658107).  
**Cannot** pass [QOJ 7185](https://qoj.ac/contest/1356/problem/7185)


## Minimum Cost Max Flow
### Description
### Test Status


## Weighted Matching
### Description

Blossom Algorithm runs in $O(EV^2)$. Not sure about the complexity of ours.  
Can solve $|V|=500$ testcases though.

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/160271)
