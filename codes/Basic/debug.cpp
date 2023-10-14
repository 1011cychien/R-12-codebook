#include <experimental/iterator>
#define all(x) begin(x), end(x)
#ifdef CKISEKI
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) cerr<<"\e[1;32m("#a") = ("<<debug_(a)<<")\e[0m\n"
#define orange(a...) cerr<<"\e[1;32m[ "#a" ] = [ "<<orange_(a)<<" ]\e[0m\n"
template <typename ...T> string debug_(T ...a) {
  stringstream ss; int f = 0;
  (..., (ss << (f++ ? ", " : "") << a));
  return ss.str();
}
template <typename I> string orange_(I L, I R) {
  stringstream ss; using namespace std::experimental;
  copy(L, R, make_ostream_joiner(ss, ", "));
  return ss.str();
}
#else
#define safe ((void)0)
#define debug(...) safe
#define orange(...) safe
#endif
