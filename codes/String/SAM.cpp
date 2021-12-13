struct SuffixAutomaton {
  struct node {
    int ch[K], len, fail, cnt, indeg;
    node(int L = 0) : ch{}, len(L), fail(0), cnt(0), indeg(0) {}
  } st[N];
  int root, last, tot;
  void extend(int c) {
    int cur = ++tot;
    st[cur] = node(st[last].len + 1);
    while (last && !st[last].ch[c]) {
        st[last].ch[c] = cur;
        last = st[last].fail;
    }
    if (!last) {
        st[cur].fail = root;
    } else {
        int q = st[last].ch[c];
        if (st[q].len == st[last].len + 1) {
            st[cur].fail = q;
        } else {
            int clone = ++tot;
            st[clone] = st[q];
            st[clone].len = st[last].len + 1;
            st[st[cur].fail = st[q].fail = clone].cnt = 0;
            while (last && st[last].ch[c] == q) {
                st[last].ch[c] = clone;
                last = st[last].fail;
            }
        }
    }
    st[last = cur].cnt += 1;
  }
  void init(const char* s) {
    root = last = tot = 1;
    st[root] = node(0);
    for (char c; c = *s; ++s) extend(c - 'a');
  }
  int q[N];
  void dp() {
    for (int i = 1; i <= tot; i++) ++st[st[i].fail].indeg;
    int head = 0, tail = 0;
    for (int i = 1; i <= tot; i++)
        if (st[i].indeg == 0) q[tail++] = i;
    while (head != tail) {
        int now = q[head++];
        if (int f = st[now].fail) {
            st[f].cnt += st[now].cnt;
            if (--st[f].indeg == 0) q[tail++] = f;
        }
    }
  }
  int run(const char* s) {
    int now = root;
    for (char c; c = *s; ++s) {
        if (!st[now].ch[c -= 'a']) return 0;
        now = st[now].ch[c];
    }
    return st[now].cnt;
  }
} SAM;
