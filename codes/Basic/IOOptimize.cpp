static inline int gc() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q &&
        (q=(p=buf)+fread(buf,1,B,stdin)) == buf)
      return EOF;
    return *p++;
}
template < typename T >
static inline bool gn( T &x ) {
  int c = gc(); T sgn = 1; x = 0;
  while(('0'>c||c>'9') && c!=EOF && c!='-') c = gc();
  if(c == '-') sgn = -1, c = gc();
  if(c == EOF) return false;
  while('0'<=c&&c<='9') x = x*10 + c - '0', c = gc();
  return x *= sgn, true;
}
