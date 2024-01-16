int fdiv(int a, int b)
{ return a / b - (a % b && (a < 0) ^ (b < 0)); }
int cdiv(int a, int b)
{ return a / b + (a % b && (a < 0) ^ (b > 0)); }
