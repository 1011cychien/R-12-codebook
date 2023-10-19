struct SVG {
  ofstream o; string c = "red";
  SVG(auto s, auto x1, auto y1, auto x2, auto y2):o(s){
    print("<svg xmlns='http://www.w3.org/2000/svg' "
        "viewBox='% % % %'>\n", x1, -y2, x2 - x1, y2 - y1);
  }
  void print(auto f) { o << f; }
  void print(const char *f, auto value, auto ...rest) {
    for (; *f; ++f) if (*f == '%') {
      o << value; print(f + 1, rest...); return;
    } else o << *f;
  }
  ~SVG() { o << "</svg>" << endl; }
  SVG &color(string nc) { return c = nc, *this; }
  void line(auto x1, auto y1, auto x2, auto y2) {
    print("<line stroke='%' stroke-width='%' "
        "x1='%' y1='%' x2='%' y2='%'/>\n",
        c, 0.1, x1, -y1, x2, -y2);
  }
  void circle(auto x, auto y, auto r) {
    print("<circle stroke='%' fill='none' "
        "cx='%' cy='%' r='%'/>\n", c, x, -y, r);
  }
  void text(auto x, auto y, string s, int w = 12) {
    print("<text x='%' y='%' font-size='%px'>%</text>",
        x, -y, w, s);
  }
};
