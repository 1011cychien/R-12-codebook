struct Circle { Point o; Real r; };

vector<Real> intersectAngle(Circle a, Circle b) {
  Real d2 = norm(a.o - b.o);
  if (norm(A.r - B.r) >= d2)
    if (A.r < B.r)
      return {-PI, PI};
    else
      return {};
  if (norm(A.r + B.r) <= d2) return {};
  Real dis = hypot(A.x - B.x, A.y - B.y);
  Real theta = atan2(B.y - A.y, B.x - A.x);
  Real phi = acos((A.r * A.r + d2 - B.r * B.r) /
      (2 * A.r * dis));
  Real L = theta - phi, R = theta + phi;
  while (L < -PI) L += PI * 2;
  while (R > PI) R -= PI * 2;
  return { L, R };
}

vector<Point> intersectPoint(Circle a, Circle b) {
  Real d=o.dis(aa.o);
  if (d >= r+aa.r || d <= fabs(r-aa.r)) return {};
  Real dt = (r*r - aa.r*aa.r)/d, d1 = (d+dt)/2;
  Point dir = (aa.o-o); dir /= d;
  Point pcrs = dir*d1 + o;
  dt=sqrt(max(0.0L, r*r - d1*d1)), dir=dir.rot90();
  return {pcrs + dir*dt, pcrs - dir*dt};
}
