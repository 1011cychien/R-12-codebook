// min{k | l <= ((ak) mod m) <= r}
optional<uint64_t> mod_min(uint32_t a, uint32_t m, uint32_t l, uint32_t r) {
	if (a == 0) return l ? nullopt : 0;
	if (auto k = uint64_t(l + a - 1) / a; k * a <= r)
		return k;
	auto b = m / a, c = m % a;
	if (auto y = mod_min(c, a, a - r % a, a - l % a))
	  return (l + *y * c + a - 1) / a + *y * b;
  return nullopt;
}
