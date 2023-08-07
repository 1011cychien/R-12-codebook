// ref: codeforces.com/gym/101201/submission/36665988
// please ensure that point strictly out of hull
pair<int, int> get_tangent(const vector<P> &v, P p) {
    const int N = v.size();
    if (p == v[0]) return {-1, -1};
    const auto cmp = [w = conj(v[0] - p)](P a, P b) {
        int qa = quad(a * w), qb = quad(b * w);
        if (qa != qb) return sgn(qa - qb);
        return sgn(cross(b, a));
    };
    const auto gao = [&](int s) {
        const auto lt = [&](int x, int y) {
            return cmp(v[x%N]-p, v[y%N]-p) == s; };
        bool up = lt(0, 1);
        int l = 0, r = N;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (lt(m, 0)) {
                if (up) r = m;
                else l = m;
            } else {
                if (lt(m, m + 1)) l = m;
                else r = m;
            }
        }
        return lt(l, r) ? r : l;
    };
    int a = gao(-1) % N, b = gao(1) % N;
    assert (cmp(v[b] - p, v[a] - p) <= 0);
    if (cmp(v[a] - p, p - v[b]) >= 0) return {-1, -1};
    return make_pair(a, b);
}
