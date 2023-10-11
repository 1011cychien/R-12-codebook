# Geometry

## Basic Geometry

### Description
- `sgn` `cross` `dot` `ori`
- `quad` `argCmp` all-integer angle compare.
- `area` be careful of type.
- `rot90` multiply by $i$ (or left turn 90 degree)
- `project` projection onto a vector
### Test Status
No test. Used extensively in other template.
TODO Center of polygon needs test.

## 2D Convex Hull

### Description
Returns strict convex hull of given points.
The result is counter-clockwise and the first point is the lex-min point.
Be carefule about edge case (0/1/2/3 points on CV)
### Test Status
Used in some contest.

## 2D Farthest Pair
### Description
Rotating caliper algorithm.
Requires the input hull be strictly convex.
### Test Status
Passed AOJ CGL.

## MinMax Enclosing Rect
### Description
Rotating caliper, but with more pointers.
### Test Status
Passed UVA 819

## Minkowski Sum
### Description
Minkowski sum of two convex hulls.
### Test Status
Used in some contest. TODO.

## Segment Intersection
### Description
Check whether the segment intersects. Touching at the ends counts.
Be careful about edge case like parallel, does touching at ends count, ...
Can be modified to `Ray` class or `Line` class.

To get the intersection point, check next part (HPI)

### Test Status
Used in many contest. Passed AOJ CGL.

## Half Plane Intersection
### Description
Calculate the area of half-plane-intersection.
The result lines will be in `q` (this is why we need the reference).
Result lines maybe wrong if the intersection area doesn't have positive area.
### Test Status
Passed 2020 Nordic NCPC Big brother.
Used in many contest.

## SegmentDist
### Description
Distance from point to segment and segment to segment.
Can be used in checking sausage intersection.
### Test Status
Passed QOJ 2444 and PTZ 19 summer D3.

## Rotating Sweep Line
### Description
A skeleton of rotating sweep line.
### Test Status
TODO. Needs template problem.

## Polygon Cut
### Description
Cut simple polygon by a line.
### Test Status
Copied from kactl. TODO.

## Point in Simple Polygon
### Description
Testing PIP.
### Test Status
Used in some contest. TODO.

## Point in Hull (Fast)
### Description
Testing PIH in $O(\log N)$.
### Test Status
[Enclosure](codeforces.com/gym/101201/problem/E)
Used in some contest.

## Tangent of Points To Hull
### Description
Tangent of point to hull in $O(\log N)$.
Requires the hull to be strictly convex.
Can be modified to find extreme point on hull.

### Test Status
[Enclosure](codeforces.com/gym/101201/problem/E)

## Circle Class & Intersection
### Description
Definition of `Cir` and some intersection function.
### Test Status
Passed AOJ CGL.

## Circle Common Tangent
### Description
Common tangent point of circle.
### Test Status
Passed AOJ CGL and [CF 128E](https://codeforces.com/problemset/problem/128/E).

## Line-Circle Intersection
### Description
The point of intersection of line and circle.
### Test Status
TODO.

## Poly-Circle Intersection
### Description
The intersection area of a circle and a simple polygon.
### Test Status
Passed AOJ CGL_7_H.
Copied from 8BQube and they say it passed HDU2892.

## Minimum Covering Circle
### Description
Get minimum covering circle in $O(N)$ expected time.
Also gives the circumcenter formula.
### Test Status
Passed TIOJ 1093, luogu P1742

## Circle Union
### Description
Calculate the area that covered by at least $k$ circle for each $k$.
Time complexity $O(N^2\log N)$.
### Test Status
Passed SPOJ.

## Polygon Union
### Description
Union area of simple polygon.
### Test Status
TODO.

## 3D Point
### Description
Basic 3d point.
- cross
- mix product
- rotate around an axis
### Test Status
`rotate_around` is copied from NaCl.
Others are tested by 3d hull.

## 3D projection
### Description
Get the 2d coordinate of the projection
of a point $p$ onto plane $q^Tx = 0$.
### Test Status
Passed [stars in a can](https://open.kattis.com/problems/starsinacan).

## 3D Convex Hull
### Description
Return the face of 3d convex hull of $N$ points.
There will be $O(N)$ faces and time complexity is $O(N^2)$.
Be careful of degenerate cases.
### Test Status
Passed SPOJ and [stars in a can](https://open.kattis.com/problems/starsinacan).
Needs test coplanar case.

## Delaunay
### Description
Delaunay triangulation.

Usage TODO.

### Test Status
Passed [Brazil subregional](https://codeforces.com/gym/104555/submission/223452683).

## kd Tree (Nearest Point)
### Description
KD Tree nearest point query.
### Test Status
TODO

## kd Closest Pair (3D ver.)
### Description
3d closest pair
### Test Status
Correct, but might be too slow. Can pass [TIOJ](https://tioj.ck.tp.edu.tw/submissions/357857) using fast hash table.  
Need more test.

## Simulated Annealing
### Description
A skeleton of simulated annealing
### Test Status
TODO.

## Triangle Centers 
### Description
Triangle centers formula.
### Test Status
No test.
