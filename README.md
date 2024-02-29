ckiseki
----

![build status](https://github.com/OmeletWithoutEgg/ckiseki/workflows/build%20codebook.pdf/badge.svg)

ICPC codebook used by team ckiseki from National Taiwan University

* [Latest content](https://github.com/OmeletWithoutEgg/ckiseki/raw/master/pdf/codebook.pdf)
* [Latest document](https://github.com/OmeletWithoutEgg/ckiseki/raw/master/docs/docs.pdf)
* [Test Status](https://omeletwithoutegg.github.io/ckiseki/)

- 在 pdf 裡面標星號的代表 not verified
- 在 .cpp 裡面放 `/* SPLIT_HASH_HERE */` 可以分段 hash

## TODO

* Make all include cpps have corresponding docs.
* Rewrite gen_content.py or refactor whole building mechanism @@

### To delete/fix/shorten
* [x] binary search on segtree
* [x] make KM modern
* [x] shorten floor sum
* [x] shorten weighted general matching
* [x] Add Manacher comment
* [x] del old fft and polynomial?
* [x] FPS
* [x] shorten SA
* [x] network simplex
* [x] 修萬能歐幾里得
* [ ] fix SAM/PalTree
* [ ] tree knapsack
* [ ] min mean cycle
* [ ] simulate annealing
* [ ] Simplex (Performance, e.g. with custom type?)
* [ ] treap
* [ ] test performance of SAIS for big strings (or vectors).
* [ ] suffix array lcp tools
* vim `Hash` command broken when searching `Hash`.
* [ ] unify `CostFlow.cpp` and `DijkstraCostFlow.cpp`.

### To add
* [x] count 3 cycle / 4 cycle
* [x] faster Pollard Rho (127(?))
* [x] bipartite independent set / vertex cover construction
* [x] LP dual formula
* [x] HLPP? $(N^2\sqrt{M})$ max-flow
* [x] Make an usable Gaussian Elimination
* [x] bounded flow?
* [x] add definition of matroid
* [ ] add simple polygon sweep line docs
* 郵局設置問題無限大extreme (aliens trick + convex 1d 1d opt)
* segment tree beats
* [邀請函](https://omeletwithoutegg.github.io/2020/11/22/TIOJ-1978/)?
* subset convolution
* add 3d geometry
* BitsetLCS with solution
* QR decomposition
* [ ] highly composite number?
* [ ] [more submodular minimization](https://noshi91.hatenablog.com/entry/2021/06/29/044225)
* [ ] add (useful) kosaraju back
* [ ] [ear decomposition](https://codeforces.com/contest/521/submission/146192598)
* [ ] min 25 篩
* [ ] [匹配相關](https://maspypy.github.io/library/flow/rank_maximal_bipartite_matching.hpp)
* [ ] sector union?
* [ ] add more derivatives/integrals
* interval container
* weighted bipartite matching in $O(N_L^{2}N_R)$
* KM, but with slope function (the best match of exactly C edges, C = $0..N$)

### Flow series
* [Network Simplex](https://gist.github.com/brunodccarvalho/fb9f2b47d7f8469d209506b336013473)/[Cost Scaling](https://ideone.com/q6PWgB)/[Capacity Scaling](https://ouuan.github.io/post/%E5%9F%BA%E4%BA%8E-capacity-scaling-%E7%9A%84%E5%BC%B1%E5%A4%9A%E9%A1%B9%E5%BC%8F%E5%A4%8D%E6%9D%82%E5%BA%A6%E6%9C%80%E5%B0%8F%E8%B4%B9%E7%94%A8%E6%B5%81%E7%AE%97%E6%B3%95/)
* [MCMF Dual](https://github.com/brianbbsu/8BQube/commit/6277ef72c0f371195d79a432e374b44ed77a9807)
* [Submodular Mincut](https://theory-and-me.hatenablog.com/entry/2020/03/17/180157)
* [最小费用可行流(?)](https://www.cnblogs.com/smashfun/p/13259192.html)

### Geometry
* [x] fix our 2d convex hull?
* [x] MinMaxEnclosing Rectangle
* [x] half plane intersection precision
* [x] rotating sweep line
* [x] convex cut
* [x] make delaunay easier to use (make postprocess voronoi)
* [x] to add
    * [x] triangle hearts?
    * [x] adaptive simpson?
    * [x] 3d point class
* [x] [3d hull test](https://vjudge.net/problem/HDU-3662)
* [x] offline PointInSimplePolygon (NaCl)
* [ ] del or fix
    * KD tree
    * KD closet pair
* [ ] convex hull trick linear?
* be careful of `std::abs<complex<int>>`
* https://vjudge.net/problem/UVA-12311
