// Divides into multiple triangle, and sum up
// test by HDU2892
llf _area(PTF pa, PTF pb, llf r) {
  if (abs(pa) < abs(pb)) swap(pa, pb);
  if (abs(pb) < eps) return 0;
  llf S, h, theta;
  llf a = abs(pb), b = abs(pa), c = abs(pb - pa);
  llf cosB = dot(pb, pb - pa) / a / c, B = acos(cosB);
  llf cosC = dot(pa, pb) / a / b, C = acos(cosC);
  if (a > r) {
    S = (C / 2) * r * r;
    h = a * b * sin(C) / c;
    if (h < r && B < PI / 2)
      S -= (acos(h / r) * r * r - h * sqrt(r*r - h*h));
  } else if (b > r) {
    theta = PI - B - asin(sin(B) / r * a);
    S = 0.5 * a*r * sin(theta) + (C - theta) / 2 * r*r;
  } else
    S = 0.5 * sin(C) * a * b;
  return S;
}
llf area_poly_circle(const vector<PTF> &poly, PTF O, llf r) {
  llf S = 0;
  for (int i = 0, N = poly.size(); i < N; ++i)
    S += _area(poly[i] - O, poly[(i + 1) % N] - O, r) *
         ori(O, poly[i], poly[(i + 1) % N]);
  return abs(S);
}
