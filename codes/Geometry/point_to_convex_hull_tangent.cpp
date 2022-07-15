#define above(P, Vi, Vj) (ori(P, Vi, Vj) > 0) // true if Vi is above Vj
#define below(P, Vi, Vj) (ori(P, Vi, Vj) < 0) // true if Vi is below Vj
// Rtangent_PointPolyC(): binary search for convex polygon right tangent
//    Input:  P = a 2D point (exterior to the polygon)
//            n = number of polygon vertices
//            V = array of vertices for a 2D convex polygon with V[n] = V[0]
//    Return: index "i" of rightmost tangent point V[i]
int Rtangent_PointPolyC(PT P, int n, PT *V) {
  int a, b, c;
  int upA, dnC;

  if (below(P, V[1], V[0]) && !above(P, V[n - 1], V[0]))
    return 0;

  for (a = 0, b = n;;) {
    c = (a + b) / 2;
    dnC = below(P, V[c + 1], V[c]);
    if (dnC && !above(P, V[c - 1], V[c]))
      return c;

    upA = above(P, V[a + 1], V[a]);
    if (upA) {
      if (dnC) {
        b = c;
      } else {
        if (above(P, V[a], V[c]))
          b = c;
        else
          a = c;
      }
    } else {
      if (!dnC) {
        a = c;
      } else {
        if (below(P, V[a], V[c]))
          b = c;
        else
          a = c;
      }
    }
  }
}

// Ltangent_PointPolyC(): binary search for convex polygon left tangent
//    Input:  P = a 2D point (exterior to the polygon)
//            n = number of polygon vertices
//            V = array of vertices for a 2D convex polygon with V[n]=V[0]
//    Return: index "i" of leftmost tangent point V[i]
int Ltangent_PointPolyC(PT P, int n, PT *V) {
  int a, b, c;
  int dnA, dnC;

  if (above(P, V[n - 1], V[0]) && !below(P, V[1], V[0]))
    return 0;

  for (a = 0, b = n;;) {
    c = (a + b) / 2;
    dnC = below(P, V[c + 1], V[c]);
    if (above(P, V[c - 1], V[c]) && !dnC)
      return c;
    dnA = below(P, V[a + 1], V[a]);
    if (dnA) {
      if (!dnC) {
        b = c;
      } else {
        if (below(P, V[a], V[c]))
          b = c;
        else
          a = c;
      }
    } else {
      if (dnC) {
        a = c;
      } else {
        if (above(P, V[a], V[c]))
          b = c;
        else
          a = c;
      }
    }
  }
}
