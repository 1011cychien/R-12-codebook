// Divides into multiple triangle, and sum up
// from 8BQube, test by HDU2892 & AOJ CGL_7_H
llf _area(PTF pa, PTF pb, llf r) {
  if (abs(pa) < abs(pb)) swap(pa, pb);
  if (abs(pb) < eps) return 0;
  llf S, h, theta;
  llf a = abs(pb), b = abs(pa), c = abs(pb - pa);
  llf cB = dot(pb, pb-pa) / a / c, B = acos_safe(cB);
  llf cC = dot(pa, pb) / a / b, C = acos_safe(cC);
  if (a > r) {
    S = (C / 2) * r * r; h = a * b * sin(C) / c;
    if (h < r && B < PI / 2)
      S -= (acos_safe(h/r)*r*r - h*sqrt_safe(r*r-h*h));
  } else if (b > r) {
    theta = PI - B - asin_safe(sin(B) / r * a);
    S = 0.5 * a*r*sin(theta) + (C-theta)/2 * r * r;
  } else
    S = 0.5 * sin(C) * a * b;
  return S;
}
llf area_poly_circle(const vector<PTF> &v, PTF O, llf r) {
  llf S = 0;
  for (size_t i = 0, N = v.size(); i < N; ++i)
    S += _area(v[i] - O, v[(i + 1) % N] - O, r) *
         ori(O, v[i], v[(i + 1) % N]);
  return abs(S);
}
