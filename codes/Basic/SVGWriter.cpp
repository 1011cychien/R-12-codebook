struct SVG {
  ofstream o;
  SVG(string fn, auto x1, auto y1, auto x2, auto y2) : o(fn) {
    o << "<svg xmlns='http://www.w3.org/2000/svg' viewBox='" << x1 << " " << -y2 << " " << x2 - x1 << " " << y2 - y1 << "'>\n";
  }
  ~SVG() { o << "</svg>" << endl; }
  void line(auto x1, auto y1, auto x2, auto y2, string c = "red") {
    o << "<line x1='" << x1 << "' y1='" << -y1 << "' x2='" << x2 << "' y2='" << -y2 << "' stroke='" + c + "'/>\n";
  }
  void circle(auto x, auto y, auto r, string c = "red") {
    o << "<circle cx='" << x << "' cy='" << -y << "' r='" << r << "' stroke='" + c + "' fill='none'/>\n";
  }
  void text(auto x, auto y, string s, int w = 12) {
    o << "<text x='" << x << "' y='" << -y << "' font-size='" << w << "px'>" + s + "</text>\n";
  }
};
