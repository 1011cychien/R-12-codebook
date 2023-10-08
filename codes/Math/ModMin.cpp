// min{k | l <= ((ak) mod m) <= r}
optional<llu> mod_min(u32 a, u32 m, u32 l, u32 r) {
	if (a == 0) return l ? nullopt : 0;
	if (auto k = llu(l + a - 1) / a; k * a <= r)
		return k;
	auto b = m / a, c = m % a;
	if (auto y = mod_min(c, a, a - r % a, a - l % a))
	  return (l + *y * c + a - 1) / a + *y * b;
  return nullopt;
}
