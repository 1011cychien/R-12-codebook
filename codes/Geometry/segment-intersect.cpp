using Point = complex<coord_t>;
struct Segment {
    Point S, L; // S + tL
    static bool valid(coord_t p, coord_t q) {
        // is there x s.t. 0 <= x <= 1 && qx == p ?
        if(q == 0) return p == 0;
        if(q < 0) q = -q, p = -p;
        return 0 <= p && p <= q;
    }
};
bool intersect(Segment A, Point P) {
    if(A.L == Point{0}) return P == A.S;
    return cross(P - A.S, A.L) == 0 &&
      Segment::valid(dot(P - A.S, A.L), norm(A.L));
}
bool intersect(Segment A, Segment B) {
    if(cross(A.L, B.L) == 0)
        return
        intersect(A, B.S) || intersect(A, B.S+B.L) ||
        intersect(B, A.S) || intersect(B, A.S+A.L);
    Point D = B.S - A.S;
    coord_t C = cross(A.L, B.L);
    return Segment::valid(cross(D, A.L), C) &&
      Segment::valid(cross(D, B.L), C);
}
