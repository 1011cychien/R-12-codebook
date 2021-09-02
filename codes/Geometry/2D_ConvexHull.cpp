template<typename PT>
vector<PT> buildConvexHull(vector<PT> d) {
  sort(ALL(d), [](const PT& a, const PT& b){
      return tie(a.x, a.y) < tie(b.x, b.y);});
  vector<PT> s(SZ(d)<<1);
  int o = 0;
  for(auto p: d) {
    while(o>=2 && cross(p-s[o-2],s[o-1]-s[o-2])<=0)
      o--;
    s[o++] = p;
  }
  for(int i=SZ(d)-2, t = o+1;i>=0;i--){
    while(o>=t&&cross(d[i]-s[o-2],s[o-1]-s[o-2])<=0)
      o--;
    s[o++] = d[i];
  }
  s.resize(o-1);
  return s;
}
