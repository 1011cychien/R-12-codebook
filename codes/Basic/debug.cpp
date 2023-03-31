#ifdef CKISEKI
#define safe cerr<<__PRETTY_FUNCTION__\
    <<" line "<<__LINE__<<" safe\n"
#define debug(a...) debug_(#a, a)
#define orange(a...) orange_(#a, a)
using std::cerr;
template <typename ...T>
void debug_(const char *s, T ...a) {
    cerr << "\e[1;32m(" << s << ") = (";
    int cnt = sizeof...(T);
    (..., (cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename Iter>
void orange_(const char *s, Iter L, Iter R) {
    cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        cerr << (f++ ? ", " : "") << *L;
    cerr << " ]\e[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) ((void)0)
#define orange(...) ((void)0)
#endif
