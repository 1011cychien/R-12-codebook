#define all(x) begin(x), end(x)
#ifdef local
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) \
  cerr<<"\e[1;32m("#a") = ("<<debug_(a)<<")\e[0m\n"
#define orange(a...) \
  orange_("\e[1;32m[ "#a" ] = [ ", a, " ]\e[0m\n")
template <typename T>
string debug_(T t) { return to_string(t); }
template <typename U, typename ...V>
string debug_(U u, V ...v) {
  return to_string(u) + ", " + debug_(v...);
}
template <typename I>
void orange_(string pre, I L, I R, string post) {
  cerr << pre;
  copy(L, R, ostream_iterator<decltype(*L)>(cerr, ", "));
  cerr << post;
}
#else
#define safe ((void)0)
#define debug(...) safe
#define orange(...) safe
#endif

