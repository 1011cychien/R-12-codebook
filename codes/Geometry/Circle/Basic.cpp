llf FMOD(llf x) {
  if (x < -PI) x += PI * 2;
  if (x > PI) x -= PI * 2;
  return x;
}
struct Circle { PTF o; llf r; };
vector<llf> intersectAngle(Circle A, Circle B) {
  PTF dir = B.o - A.o; llf d2 = norm(dir);
  if (norm(A.r - B.r) >= d2) // norm(x) := |x|^2
    if (A.r < B.r) return {-PI, PI}; // A in B
    else return {}; // B in A
  if (norm(A.r + B.r) <= d2) return {};
  llf dis = abs(dir), theta = arg(dir);
  llf phi = acos((A.r * A.r + d2 - B.r * B.r) /
      (2 * A.r * dis));
  llf L = FMOD(theta - phi), R = FMOD(theta + phi);
  return { L, R };
}
vector<PTF> intersectPoint(Circle a, Circle b) {
  llf d = abs(a.o - b.o);
  if (d >= b.r+a.r || d <= abs(b.r-a.r)) return {};
  llf dt = (b.r*b.r - a.r*a.r)/d, d1 = (d+dt)/2;
  PTF dir = (a.o - b.o) / d;
  PTF u = dir*d1 + b.o;
  PTF v = rot90(dir) * sqrt(max<llf>(0, b.r*b.r-d1*d1));
  return {u + v, u - v};
}
