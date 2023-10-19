struct P3 {
  lld x, y, z;
  P3 operator^(const P3 &b) const {
    return {y*b.z-b.y*z, z*b.x-b.z*x, x*b.y-b.x*y};
  }
  //Azimuthal angle (longitude) to x-axis. \in [-pi, pi]
	llf phi() const { return atan2(y, x); }
	//Zenith angle (latitude) to the z-axis. \in [0, pi]
	llf theta() const { return atan2(sqrt(x*x+y*y),z); }
};
P3 ver(P3 a, P3 b, P3 c) { return (b - a) ^ (c - a); }
lld volume(P3 a, P3 b, P3 c, P3 d) {
  return dot(ver(a, b, c), d - a);
}
P3 rotate_around(P3 p, llf angle, P3 axis) {
  llf s = sin(angle), c = cos(angle);
  P3 u = normalize(axis);
  return u*dot(u, p)*(1-c) + p * c + cross(u, p)*s;
}
