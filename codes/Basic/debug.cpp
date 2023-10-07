#define all(x) begin(x), end(x)
#ifdef CKISEKI
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) debug_(#a, a)
#define orange(a...) orange_(#a, a)
template <typename ...T>
void debug_(const char *s, T ...a) {
    cerr << "\e[1;32m(" << s << ") = (";
    int cnt = sizeof...(T);
    (..., (cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename I>
void orange_(const char *s, I L, I R) {
    cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        cerr << (f++ ? ", " : "") << *L;
    cerr << " ]\e[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) safe
#define orange(...) safe
#endif
