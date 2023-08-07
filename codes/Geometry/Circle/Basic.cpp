llf FMOD(llf x) {
  if (x < -PI) x += PI * 2;
  if (x > PI) x -= PI * 2;
  return x;
}
struct Cir { PTF o; llf r; };
// be carefule when tangent
vector<llf> intersectAngle(Cir a, Cir b) {
  PTF dir = b.o - a.o; llf d2 = norm(dir);
  if (norm(a.r - b.r) >= d2) { // norm(x) := |x|^2
    if (a.r < b.r) return {-PI, PI}; // a in b
    else return {}; // b in a
  } else if (norm(a.r + b.r) <= d2) return {};
  llf dis = abs(dir), theta = arg(dir);
  llf phi = acos((a.r * a.r + d2 - b.r * b.r) /
      (2 * a.r * dis)); // is acos_safe needed ?
  llf L = FMOD(theta - phi), R = FMOD(theta + phi);
  return { L, R };
}
vector<PTF> intersectPoint(Cir a, Cir b) {
  llf d = abs(a.o - b.o);
  if (d > b.r+a.r || d < abs(b.r-a.r)) return {};
  llf dt = (b.r*b.r - a.r*a.r)/d, d1 = (d+dt)/2;
  PTF dir = (a.o - b.o) / d;
  PTF u = dir * d1 + b.o;
  PTF v = rot90(dir) * sqrt(max(0.0l, b.r*b.r-d1*d1);
  return {u + v, u - v};
}
// test @ AOJ CGL probs
