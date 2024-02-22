// A, B are strict convex hull rotate to min by (X, Y)
vector<P> Minkowski(vector<P> A, vector<P> B) {
  const int N = (int)A.size(), M = (int)B.size();
  vector<P> sa(N), sb(M), C(N + M + 1);
  for (int i = 0; i < N; i++) sa[i] = A[(i+1)%N]-A[i];
  for (int i = 0; i < M; i++) sb[i] = B[(i+1)%M]-B[i];
  C[0] = A[0] + B[0];
  for (int i = 0, j = 0; i < N || j < M; ) {
    P e = (j>=M || (i<N && cross(sa[i], sb[j])>=0))
      ? sa[i++] : sb[j++];
    C[i + j] = e;
  }
  partial_sum(all(C), C.begin()); C.pop_back();
  return convex_hull(C); // just to remove colinear
} // be careful if min(|A|,|B|)<=2
