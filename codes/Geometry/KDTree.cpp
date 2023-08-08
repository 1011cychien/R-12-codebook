struct KDTree {
  struct Node {
    int x, y, x1, y1, x2, y2; int id, f;
    Node *L, *R;
  } tree[maxn], *root;
  lld dis2(int x1, int y1, int x2, int y2) {
    lld dx = x1 - x2, dy = y1 - y2;
    return dx * dx + dy * dy;
  }
  static bool cmpx(Node& a, Node& b){return a.x<b.x;}
  static bool cmpy(Node& a, Node& b){return a.y<b.y;}
  void init(vector<pair<int,int>> &ip) {
    const int n = ip.size();
    for (int i = 0; i < n; i++) {
      tree[i].id = i;
      tree[i].x = ip[i].first;
      tree[i].y = ip[i].second;
    }
    root = build_tree(0, n-1, 0);
  }
  Node* build_tree(int L, int R, int d) {
    if (L>R) return nullptr;
    int M = (L+R)/2; tree[M].f = d%2;
    nth_element(tree+L,tree+M,tree+R+1,d%2?cmpy:cmpx);
    tree[M].x1 = tree[M].x2 = tree[M].x;
    tree[M].y1 = tree[M].y2 = tree[M].y;
    tree[M].L = build_tree(L, M-1, d+1);
    tree[M].R = build_tree(M+1, R, d+1);
    for (Node *s: {tree[M].L, tree[M].R}) if (s) {
      tree[M].x1 = min(tree[M].x1, s->x1);
      tree[M].x2 = max(tree[M].x2, s->x2);
      tree[M].y1 = min(tree[M].y1, s->y1);
      tree[M].y2 = max(tree[M].y2, s->y2);
    }
    return tree+M;
  }
  int touch(Node* r, int x, int y, lld d2){
    lld dis = sqrt(d2)+1;
    if (x<r->x1-dis || x>r->x2+dis ||
        y<r->y1-dis || y>r->y2+dis)
      return 0;
    return 1;
  }
  using P = pair<lld, int>;
  void dfs(int x, int y, P &best, Node *r) {
    if (!r || !touch(r, x, y, best.first)) return;
    P cur(dis2(r->x, r->y, x, y), r->id);
    best = min(best, cur);
    // search order depends on split dim
    if ((r->f == 1 ? y < r->y : x < r->x)) {
      dfs(x, y, best, r->L);
      dfs(x, y, best, r->R);
    } else {
      dfs(x, y, best, r->R);
      dfs(x, y, best, r->L);
    }
  }
  int query(int x, int y) {
    P best(102938475612345678LL, 1029384756);
    dfs(x, y, best, root);
    return best.second;
  }
} tree;
