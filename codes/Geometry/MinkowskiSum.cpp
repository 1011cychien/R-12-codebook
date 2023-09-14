// A, B are convex hull rotate to min by (X, Y)
vector<P> Minkowski(vector<P> A, vector<P> B) {
  vector<P> C(1, A[0] + B[0]), s1, s2;
  const int N = (int)A.size(), M = (int)B.size();
  for(int i = 0; i < N; ++i)
    s1.pb(A[(i + 1) % N] - A[i]);
  for(int i = 0; i < M; i++)
    s2.pb(B[(i + 1) % M] - B[i]);
  for(int i = 0, j = 0; i < N || j < M;)
    if (j >= N || (i < M && cross(s1[i], s2[j]) >= 0))
      C.pb(C.back() + s1[i++]);
    else
      C.pb(C.back() + s2[j++]);
  return hull(C), C;
}
