__gnu_cxx::sfmt19937 rnd(7122);
namespace Treap {
  #define sz(x) ((x) ? ((x)->size) : 0)
  struct node{
    int size; uint32_t pri;
    node *lc, *rc, *pa;
    node():size(0),pri(rnd()),lc(0),rc(0),pa(0) {}
    void pull() {
      size = 1; pa = nullptr;
      if (lc) { size += lc->size; lc->pa = this; }
      if (rc) { size += rc->size; rc->pa = this; }
    }
  };
  node* merge(node* L, node* R) {
    if (not L or not R) return L ? L : R;
    if (L->pri > R->pri) {
      return L->rc = merge(L->rc, R), L->pull(), L;
    } else {
      return R->lc = merge(L, R->lc), R->pull(), R;
    }
  }
  void splitBySize(node*o,int k,node*&L,node*&R) {
    if (not o) L = R = nullptr;
    else if (int s = sz(o->lc) + 1; s <= k) {
      L=o; splitBySize(o->rc, k-s, L->rc, R); L->pull();
    } else {
      R=o; splitBySize(o->lc, k, L, R->lc); R->pull();
    }
  } // sz(L) == k
  int getRank(node *o) { // 1-base
    int r = sz(o->lc) + 1;
    for (; o->pa != nullptr; o = o->pa)
      if (o->pa->rc == o) r += sz(o->pa->lc) + 1;
    return r;
  }
  #undef sz
}
