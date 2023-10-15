#define all(x) begin(x), end(x)
#ifdef CKISEKI
#include <experimental/iterator>
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) cerr<<"\e[1;32m("#a") = ("<<debug_(a)<<")\e[0m\n"
#define orange(a...) cerr<<"\e[1;33m[ "#a" ] = [ "<<orange_(a)<<" ]\e[0m\n"
auto debug_(auto ...a) {
  stringstream ss; int f = 0;
  (..., (ss << (f++ ? ", " : "") << a));
  return ss.str();
}
auto orange_(auto L, auto R) {
  stringstream ss; using namespace std::experimental;
  copy(L, R, make_ostream_joiner(ss, ", "));
  return ss.str(); // or ostream_iterator<decltype(*L)>
}
#else
#define safe ((void)0)
#define debug(...) safe
#define orange(...) safe
#endif
