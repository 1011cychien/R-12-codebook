const int BITS = 30;

struct Basis {
    array<pair<int, int>, BITS> b;
    Basis() { b.fill({0, numeric_limits<int>::min()}); }
    void add(int x, int p) {
        for (int i = BITS - 1; i >= 0; i--) if ((x >> i) & 1) {
            if (b[i].first == 0) {
                b[i] = {x, p};
                return;
            }
            if (b[i].second < p) {
                swap(b[i].first, x);
                swap(b[i].second, p);
            }
            x ^= b[i].first;
        }
    }
    int query_kth(int v, int k) {
        vector<pair<int,int>> tmp;
        for (int i = 0; i < BITS; i++) {
            if (b[i].first == 0) continue;
            tmp.emplace_back(b[i].first, i);
        }
        if (k >= (1 << tmp.size())) return -1;
        for (int i = int(tmp.size()) - 1; i >= 0; i--) {
            int j = tmp[i].second;
            if ((k >> i & 1) ^ (v >> j & 1))
                v ^= tmp[i].first;
        }
        return v;
    }
    Basis filter(int l) {
        Basis res = *this;
        for (int i = 0; i < BITS; i++)
            if (res.b[i].second < l)
                res.b[i] = {0, numeric_limits<int>::min()};
        return res;
    }
};
