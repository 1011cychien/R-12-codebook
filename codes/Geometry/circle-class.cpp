struct Circle { Pointf o; llf r; };

vector<llf> intersectAngle(Circle A, Circle B) {
  Pointf dir = B.o - A.o; llf d2 = norm(dir);
  if (norm(A.r - B.r) >= d2)
    if (A.r < B.r) return {-PI, PI}; // special
    else return {};
  if (norm(A.r + B.r) <= d2) return {};
  llf dis = abs(dir), theta = arg(dir);
  llf phi = acos((A.r * A.r + d2 - B.r * B.r) /
      (2 * A.r * dis));
  llf L = theta - phi, R = theta + phi;
  while (L < -PI) L += PI * 2;
  while (R > PI) R -= PI * 2;
  return { L, R };
}

vector<Pointf> intersectPoint(Circle a, Circle b) {
  llf d = abs(a.o - b.o);
  if (d >= b.r+a.r || d <= abs(b.r-a.r)) return {};
  llf dt = (b.r*b.r - a.r*a.r)/d, d1 = (d+dt)/2;
  Pointf dir = (a.o - b.o); dir /= d;
  Pointf pcrs = dir*d1 + b.o;
  dt=sqrt(max(0.0L, b.r*b.r-d1*d1)), dir = rot90(dir);
  return {pcrs + dir*dt, pcrs - dir*dt};
}
