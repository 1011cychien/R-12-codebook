int Rtan(PT P, int n, PT *V) {
  if (n == 1)
    return 0;
  int a, b, c;
  int upA, dnC;
  if (below(P, V[1], V[0]) && !above(P, V[n - 1], V[0]))
    return 0;
  for (a = 0, b = n;;) {
    c = (a + b) / 2;
    dnC = not above(P, V[c + 1], V[c]);
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

int Ltan(PT P, int n, PT *V) {
  if (n == 1)
    return 0;
  int a, b, c;
  int dnA, dnC;
  if (above(P, V[n - 1], V[0]) && !below(P, V[1], V[0]))
    return 0;
  for (a = 0, b = n;;) {
    c = (a + b) / 2;
    dnC = below(P, V[c + 1], V[c]);
    if (not below(P, V[c - 1], V[c]) && !dnC)
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
