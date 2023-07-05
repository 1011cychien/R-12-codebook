template <typename F = double>
struct SVGWriter {
  FILE *f;
  F sc = 20;
  SVGWriter(char *name, F u, F l, F d, F r) : f(fopen(name, "w")) {
    fprintf(f, "<svg xmlns='http://www.w3.org/2000/svg' viewBox='%f %f %f %f'>\n", u, l, d, r);
  }
  ~SVGWriter() {
    fputs("</svg>", f);
    fclose(f);
  }
  void line(F ax, F ay, F bx, F by, const char *color = "red") {
    ax = ax * sc, ay = ay * sc, bx = bx * sc, by = by * sc;
    fprintf(f, "<line x1='%f' y1='%f' x2='%f' y2='%f' stroke='%s'/>\n", ax, -ay, bx, -by, color);
  }
  void circle(F ax, F ay, F r = 0.5, const char *color = "red") {
    ax = ax * sc, ay = ay * sc, r = sc * r;
    fprintf(f, "<circle cx='%f' cy='%f' r='%f' stroke='%s' fill='none'/>\n", ax, -ay, r, color);
  }
  void text(F ax, F ay, const char *s, int fSize = 12) {
    ax = ax * sc, ay = ay * sc;
    fprintf(f, "<text x='%f' y='%f' font-size='%dpx'>%s</text>\n", ax, -ay, fSize, s);
  }
};
