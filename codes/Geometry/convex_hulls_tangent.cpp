// RLtangent_PolyPolyC(): get the RL tangent between two convex polygons
//    Input:  m = number of vertices in polygon 1
//            V = array of vertices for convex polygon 1 with V[m]=V[0]
//            n = number of vertices in polygon 2
//            W = array of vertices for convex polygon 2 with W[n]=W[0]
//    Output: *t1 = index of tangent point V[t1] for polygon 1
//            *t2 = index of tangent point W[t2] for polygon 2
void RLtangent_PolyPolyC(int m, PT *V, int n, PT *W, int *t1, int *t2) {
  int ix1, ix2; // search indices for polygons 1 and 2

  // first get the initial vertex on each polygon
  ix1 = Rtangent_PointPolyC(W[0], m, V);   // right tangent from W[0] to V
  ix2 = Ltangent_PointPolyC(V[ix1], n, W); // left tangent from V[ix1] to W

  // ping-pong linear search until it stabilizes
  int done = false; // flag when done
  while (done == false) {
    done = true; // assume done until...
    while (ori(W[ix2], V[ix1], V[ix1 + 1]) <= 0) {
      ++ix1; // get Rtangent from W[ix2] to V
    }
    while (ori(V[ix1], W[ix2], W[ix2 - 1]) >= 0) {
      --ix2;        // get Ltangent from V[ix1] to W
      done = false; // not done if had to adjust this
    }
  }
  *t1 = ix1;
  *t2 = ix2;
  return;
}
