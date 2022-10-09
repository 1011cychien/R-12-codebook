template <typename Val, typename SVal> class LCT {
  struct node {
    int pa, ch[2];
    bool rev;
    Val v, v_prod, v_rprod;
    SVal sv, sub, vir;
    node() : pa{0}, ch{0, 0}, rev{false}, v{}, v_prod{}, v_rprod{}, sv{}, sub{}, vir{} {};
  };
  vector<node> nodes;

  bool is_root(int u) const {
    const int p = nodes[u].pa;
    return nodes[p].ch[0] != u and nodes[p].ch[1] != u;
  }
  bool is_rch(int u) const {
    return (not is_root(u)) and nodes[nodes[u].pa].ch[1] == u;
  }
  void down(int u) {
    auto &cnode = nodes[u];
    if (not cnode.rev) return;
    if (cnode.ch[0]) set_rev(cnode.ch[0]);
    if (cnode.ch[1]) set_rev(cnode.ch[1]);
    cnode.rev = false;
  }
  void up(int u) {
    auto &cnode = nodes[u];
    cnode.v_prod = nodes[cnode.ch[0]].v_prod;
    cnode.v_prod = cnode.v_prod * cnode.v;
    cnode.v_prod = cnode.v_prod * nodes[cnode.ch[1]].v_prod;
    cnode.v_rprod = nodes[cnode.ch[1]].v_rprod;
    cnode.v_rprod = cnode.v_rprod * cnode.v;
    cnode.v_rprod = cnode.v_rprod * nodes[cnode.ch[0]].v_rprod;
    cnode.sub = cnode.vir + nodes[cnode.ch[0]].sub + nodes[cnode.ch[1]].sub + cnode.sv;
  }
  void set_rev(int u) {
    swap(nodes[u].ch[0], nodes[u].ch[1]);
    swap(nodes[u].v_prod, nodes[u].v_rprod);
    nodes[u].rev ^= 1;
  }
  void rotate(int u) {
    int f = nodes[u].pa, g = nodes[f].pa;
    int l = is_rch(u);
    if (nodes[u].ch[l ^ 1])
      nodes[nodes[u].ch[l ^ 1]].pa = f;
    if (not is_root(f))
      nodes[g].ch[is_rch(f)] = u;
    nodes[f].ch[l] = nodes[u].ch[l ^ 1];
    nodes[u].ch[l ^ 1] = f;
    nodes[u].pa = g, nodes[f].pa = u;
    up(f);
  }
  void splay(int u) {
    vector<int> stk = {u};
    while (not is_root(stk.back()))
      stk.push_back(nodes[stk.back()].pa);
    while (not stk.empty()) {
      down(stk.back());
      stk.pop_back();
    }
    for (int f = nodes[u].pa; not is_root(u); f = nodes[u].pa) {
      if (not is_root(f))
        rotate(is_rch(u) == is_rch(f) ? f : u);
      rotate(u);
    }
    up(u);
  }
  void access(int x) {
    for (int u = x, last = 0; u; u = nodes[u].pa) {
      splay(u);
      nodes[u].vir += nodes[nodes[u].ch[1]].sub;
      nodes[u].vir -= nodes[last].sub;
      nodes[u].ch[1] = last;
      up(last = u);
    }
    splay(x);
  }
  int find_root(int u) {
    int la = 0;
    for (access(u); u; u = nodes[u].ch[0])
      down(la = u);
    return la;
  }
  void split(int x, int y) {
    change_root(x);
    access(y);
  }
  void change_root(int u) {
    access(u);
    set_rev(u);
  }
public:
  LCT(int n = 0) : nodes(n + 1) {}
  int add(const Val &v = {}) {
    nodes.push_back(v);
    return int(nodes.size()) - 2;
  }
  int add(Val &&v) {
    nodes.emplace_back(move(v));
    return int(nodes.size()) - 2;
  }
  void set_val(int u, const Val &v) {
    splay(++u); nodes[u].v = v; up(u);
  }
  void set_sval(int u, const SVal &v) {
    splay(++u); nodes[u].sv = v; up(u);
  }
  Val query(int x, int y) {
    split(++x, ++y);
    return nodes[y].v_prod;
  }
  SVal subtree(int p, int u) {
    change_root(++p); access(++u);
    return nodes[u].vir + nodes[u].sv;
  }
  bool connected(int u, int v) { return find_root(++u) == find_root(++v); }
  void link(int x, int y) {
    change_root(++x); access(++y);
    nodes[y].vir += nodes[x].sub;
    up(nodes[x].pa = y);
  }
  void cut(int x, int y) {
    split(++x, ++y);
    nodes[y].ch[0] = nodes[x].pa = 0;
    up(y);
  }
};
