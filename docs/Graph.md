# Graph

## 2-SAT (SCC)
### Description
Kosaraju and 2-SAT construction.
Don't forget we can do bitset optimization.

To use 2-SAT, $2i$ and $2i+1$ represents $x$ and $\neg x$.
$x \lor x$ or $\neg x \lor \neg x$ is OK.
### Test Status
Passed CSES Giant Pizza and CF Radio Stations.

## BCC
### Description
Gives AP and bridge and `bcc_id`.
`bcc_id[edge_id]` is the bcc of the edge.
### Test Status
TODO

## Round Square Tree
### Description
Or block-cut-tree. Useful tree for "simple path" queries.
There will be at most $2N$ vertices in the new tree.
### Test Status
Passed 2020 Shanghai K

## Edge TCC
### Description
Edge triconnected component.
### Test Status
Passed yosupo library checker.

## Centroid Decomposition
### Description
Mark a vertex or query the sum of distance from a vertex to
all marked vertices.
### Test Status
Need rewrite or smt.

## DMST
### Description
Directed Minimum Spanning Tree in $O(E\log ^2 E)$.
Use mergable heap instead of small-to-big for better complexity?
### Test Status
Passed yosupo library checker.

## Dominator Tree
### Description
Dominator tree in $O(E\log V)$.
The ancestor relation on the tree is the
"must-pass-from-source" relation in original graph.

### Test Status
Passed yosupo library checker.

## Lowbit Decomposition
### Description
Some chain decomposition of tree.
### Test Status
TODO

## Manhattan MST
### Description
Minimum Spanning Tree of manhattan distance.
### Test Status
The code is from kactl.

## MaximalClique
### Description
Enumerate maximal clique.
Time complexity $O(n3^(n/3))$ or $O(nC)$ where $C$
is the number of such cliques.
### Test Status
Can run on $n=80$ on TIOJ.

## Maximum Clique (Dyn)
### Description
Get maximum clique with ?? time complexity.

### Test Status
kactl says it can run on $n=155$.
For $n=100$ on POJ, runs in 32ms.

## Minimum Mean Cycle
### Description
$O(V(V+E))$ find min mean cycle.
Too rare to use so needs shorten.
### Test Status
Passed a UVa problem with $n=50$.

## Mo's Algorithm on Tree
### Description
Pseudo code of mo's algo on tree.
`push` means XOR the contribution.
### Test Status
TODO

## Tree Hashing
### Description
Some PRNG random hash.
### Test Status
Passed UOJ 763.

## Virtual Tree
### Description
Dependency: `lca`.
Gives the critital nodes of given subset.
Always include the original root.
The edges are given in rooted tree format.
### Test Status
Used in contest. TODO.
