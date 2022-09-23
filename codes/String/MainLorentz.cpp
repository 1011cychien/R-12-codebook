vector<tuple<tuple<size_t, size_t, int, int>>> reps;
void find_repetitions(const string &s, int shift = 0) {
  if (s.size() <= 1)
    return;
  const size_t nu = s.size() / 2, nv = s.size() - nu;
  string u = s.substr(0, nu), v = s.substr(nu);
  string ru(u.rbegin(), u.rend());
  string rv(v.rbegin(), v.rend());
  find_repetitions(u, shift);
  find_repetitions(v, shift + nu);
  auto z1 = Zalgo(ru), z2 = Zalgo(v + '#' + u),
       z3 = Zalgo(ru + '#' + rv), z4 = Zalgo(v);
  for (size_t cntr = 0; cntr < s.size(); cntr++) {
    size_t l; int k1, k2;
    if (cntr < nu) {
      l = nu - cntr;
      k1 = l < z1.size() ? z1[l] : 0;
      k2 = n + 1 - l < z2.size() ? z2[n + 1 - l] : 0;
    } else {
      l = cntr - nu + 1;
      k1 = n + 1 - l < z3.size() ? z3[n + 1 - l] : 0;
      k2 = l < z4.size() ? z4[l] : 0;
    }
    if (k1 + k2 >= l)
      reps.emplace_back(cntr, l, k1, k2);
  }
}
