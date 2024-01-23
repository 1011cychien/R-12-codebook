lld fdiv(lld a, lld b)
{ return a / b - (a % b && (a < 0) ^ (b < 0)); }
lld cdiv(lld a, lld b)
{ return a / b + (a % b && (a < 0) ^ (b > 0)); }
