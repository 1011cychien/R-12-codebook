ckiseki
----

![build status](https://github.com/OmeletWithoutEgg/ckiseki/workflows/build%20codebook.pdf/badge.svg)

ICPC codebook used by team ckiseki from National Taiwan University

The latest PDF build is available [here](https://github.com/OmeletWithoutEgg/ckiseki/raw/master/pdf/codebook.pdf)

## TODO

### To delete/fix/shorten
* [ ] fix SAM/PalTree
* binary search on segtree
* tree knapsack
* min mean cycle
* simulate annealing

* [ ] del old fft and polynomial?
* [ ] shorten SA
* [ ] make KM modern
* shorten weighted general matching
* shorten floor sum


### To add
* [ ] bipartite independent set / vertex cover construction
* [ ] count 3 cycle / 4 cycle
* [ ] faster Pollard Rho (127(?))
* 郵局設置問題無限大extreme
* segment tree beats
* [邀請函](https://omeletwithoutegg.github.io/2020/11/22/TIOJ-1978/)?
* subset convolution
* bounded flow?
* bipartite coloring on library checker
* Simplex (e.g. with custom type?)

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
* [ ] [3d hull test](https://vjudge.net/problem/HDU-3662)
* [ ] to add
    * [ ] triangle hearts?
    * [ ] adaptive simpson?
    * [ ] 3d point class
* [ ] del or fix
    * KD tree
    * KD closet pair
* [ ] convex cut
* [ ] angle compare in tangent line, further compare by abs?
* [ ] offline PointInSimplePolygon (NaCl)
* [ ] make delaunay easier to use (make postprocess)
* be careful of `std::abs<complex<int>>`
* convex hull trick linear?
* https://vjudge.net/problem/UVA-12311
