bool DIP(const auto &p, int i, P dir) {
  const int n = (int)p.size();
  P A = p[i+1==n ? 0 : i+1] - p[i];
  P B = p[i==0 ? n-1 : i-1] - p[i];
  if (auto C = cross(A, B); C < 0)
    return cross(A, dir) >= 0 || cross(dir, B) >= 0;
  else
    return cross(A, dir) >= 0 && cross(dir, B) >= 0;
} // is Seg(p[i], p[i]+dir*eps) in p? (non-strict)
// p is counterclockwise simple polygon
