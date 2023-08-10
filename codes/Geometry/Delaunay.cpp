bool in_cc(const array<P,3> &p, P q) {
    i128 det = 0;
    for (int i = 0; i < 3; i++)
        det += i128(norm(p[i]) - norm(q)) *
            cross(p[(i+1)%3] - q, p[(i+2)%3] - q);
    return det > 0;
}
/* Delaunay Triangulation:
Given a sets of points on 2D plane, find a
triangulation such that no points will strictly
inside circumcircle of any triangle.
find(root, p) : return a triangle contain given point
add_point : add a point into triangulation
A Triangle is in triangulation iff. its has_chd is 0.
Region of triangle u: iterate each u.e[i].tri,
each points are u.p[(i+1)%3], u.p[(i+2)%3]
Voronoi diagram: for each triangle in triangulation,
the bisector of all its edges will split the region.
nearest point will belong to the triangle containing it
 */
#define L(i) ((i)==0 ? 2 : (i)-1)
#define R(i) ((i)==2 ? 0 : (i)+1)
#define FOR for (int i = 0; i < 3; i++)
struct Tri;
struct E {
  Tri *t; int side; E() : t(0), side(0) {}
  E(Tri *_t, int _side) : t(_t), side(_side){}
};
struct Tri {
  array<P,3> p; array<Tri*,3> ch; array<E,3> e;
  Tri(){} Tri(P a, P b, P c) : p{a, b, c}, ch{} {}
  bool has_chd() const { return ch[0] != nullptr; }
  bool contains(P q) const {
    FOR if (ori(p[i], p[R(i)], q) < 0) return false;
    return true;
  }
} pool[maxn * 10], *it;
void link(E a, E b) {
  if (a.t) a.t->e[a.side] = b;
  if (b.t) b.t->e[b.side] = a;
}
struct Trigs {
  Tri *root;
  Trigs() {
    root = // should at least contain all points
      new(it++) Tri(P(-C, -C), P(C*2, -C), P(-C, C*2));
  }
  void add_point(P p) { add_point(find(p, root), p); }
  static Tri* find(P p, Tri *r) {
    while (r->has_chd()) for (Tri *c: r->ch)
        if (c && c->contains(p)) { r = c; break; }
    return r;
  }
  void add_point(Tri *r, P p) {
    array<Tri*, 3> t;
    /* split it into three triangles */
    FOR t[i] = new(it++) Tri(r->p[i], r->p[R(i)], p);
    FOR link(E(t[i], 0), E(t[R(i)], 1));
    FOR link(E(t[i], 2), r->e[L(i)]);
    r->ch = t;
    FOR flip(t[i], 2);
  }
  void flip(Tri* A, int a) {
    auto [B, b] = A->e[a];
    if (!B || !in_cc(A->p, B->p[b])) return;
    /* flip edge between A, B */
    Tri *X = new(it++)Tri(A->p[R(a)],B->p[b],A->p[a]);
    Tri *Y = new(it++)Tri(B->p[R(b)],A->p[a],B->p[b]);
    link(E(X,0), E(Y,0));
    link(E(X,1), A->e[L(a)]); link(E(X,2), B->e[R(b)]);
    link(E(Y,1), B->e[L(b)]); link(E(Y,2), A->e[R(a)]);
    A->ch = B->ch = {X, Y, nullptr};
    flip(X, 1); flip(X, 2); flip(Y, 1); flip(Y, 2);
  }
};
vector<Tri*> res; set<Tri*> vis;
void go(Tri *now) { // store all tri into res
  if (!vis.insert(now).second) return;
  if (!now->has_chd()) return res.push_back(now);
  for (Tri *c: now->ch) if (c) go(c);
}
void build(vector<P> &ps) {
  it = pool; res.clear(); vis.clear();
  shuffle(ps.begin(), ps.end(), mt19937(114514));
  Trigs tr; for (P p: ps) tr.add_point(p);
  go(tr.root); // use `res` afterwards
}
