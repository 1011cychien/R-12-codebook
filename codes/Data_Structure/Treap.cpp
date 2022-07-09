namespace Treap{
  #define sz( x ) ( ( x ) ? ( ( x )->size ) : 0 )
  struct node{
    int size;
    uint32_t pri;
    node *lc, *rc, *pa;
    node():size(0),pri(rand()),lc(0),rc(0),pa(0){}
    void pull() {
      size = 1; pa = nullptr;
      if ( lc ) { size += lc->size; lc->pa = this; }
      if ( rc ) { size += rc->size; rc->pa = this; }
    }
  };
  node* merge( node* L, node* R ) {
    if ( not L or not R ) return L ? L : R;
    if ( L->pri > R->pri ) {
      L->rc = merge( L->rc, R ); L->pull();
      return L;
    } else {
      R->lc = merge( L, R->lc ); R->pull();
      return R;
    }
  }
  void split_by_size( node*rt,int k,node*&L,node*&R ) {
    if ( not rt ) L = R = nullptr;
    else if( sz( rt->lc ) + 1 <= k ) {
      L = rt;
      split_by_size( rt->rc,k-sz(rt->lc)-1,L->rc,R );
      L->pull();
    } else {
      R = rt;
      split_by_size( rt->lc, k, L, R->lc );
      R->pull();
    }
  } // sz(L) == k
  int getRank(node *o) { // 1-base
    int r = sz(o->lc) + 1;
    for (;o->pa != nullptr; o = o->pa)
      if (o->pa->rc == o) r += sz(o->pa->lc) + 1;
    return r;
  }
  #undef sz
}
