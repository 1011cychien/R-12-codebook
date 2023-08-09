vector<PTF> LineCircleInter(PTF p1, PTF p2, PTF o, llf r) {
  PTF ft = p1 + project(o-p1, p2-p1), vec = p2-p1;
  llf dis = abs(o - ft);
  if (abs(dis - r) < eps) return {ft};
  if (dis > r) return {};
  vec = vec * sqrt(r * r - dis * dis) / abs(vec);
  return {ft + vec, ft - vec}; // sqrt_safe?
}
