#define above(P, Vi, Vj) (ori(P, Vi, Vj) > 0) // true if Vi is above Vj
#define below(P, Vi, Vj) (ori(P, Vi, Vj) < 0) // true if Vi is below Vj
// Rtangent_PointPolyC(): binary search for convex polygon right tangent
//    Input:  P = a 2D point (exterior to the polygon)
//            n = number of polygon vertices
//            V = array of vertices for a 2D convex polygon with V[n] = V[0]
//    Return: index "i" of rightmost tangent point V[i]
int Rtangent_PointPolyC(PT P, int n, PT *V) {
  if (n == 1) return 0;
  if (below(P, V[1], V[0]) && !above(P, V[n - 1], V[0]))
    return 0;
  for (int a = 0, b = n;;) {
    int c = (a + b) / 2, dnC = not above(P, V[c + 1], V[c]);
    if (dnC && !above(P, V[c - 1], V[c])) return c;
    if (above(P, V[a + 1], V[a]))
      ((dnC || above(P, V[a], V[c])) ? b : a) = c;
    else
      ((!dnC || !below(P, V[a], V[c])) ? a : b) = c;
  }
}

// Ltangent_PointPolyC(): binary search for convex polygon left tangent
//    Input:  P = a 2D point (exterior to the polygon)
//            n = number of polygon vertices
//            V = array of vertices for a 2D convex polygon with V[n]=V[0]
//    Return: index "i" of leftmost tangent point V[i]
int Ltangent_PointPolyC(PT P, int n, PT *V) {
  if (n == 1) return 0;
  if (above(P, V[n - 1], V[0]) && !below(P, V[1], V[0]))
    return 0;
  for (int a = 0, b = n;;) {
    int c = (a + b) / 2, dnC = below(P, V[c + 1], V[c]);
    if (!below(P, V[c - 1], V[c]) && !dnC) return c;
    if (below(P, V[a + 1], V[a]))
      ((!dnC || below(P, V[a], V[c])) ? b : a) = c;
    else
      ((dnC || !above(P, V[a], V[c])) ? a : b) = c;
  }
}
