#ifdef KISEKI
#define safe cerr<<__PRETTY_FUNCTION__\
    <<" line "<<__LINE__<<" safe\n"
#define debug(a...) qwerty(#a, a)
#define orange(a...) dvorak(#a, a)
using std::cerr;
template <typename ...T>
void qwerty(const char *s, T ...a) {
    cerr << "\e[1;32m(" << s << ") = (";
    int cnt = sizeof...(T);
    (..., (cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename Iter>
void dvorak(const char *s, Iter L, Iter R) {
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
