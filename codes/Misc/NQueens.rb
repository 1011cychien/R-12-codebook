def solve(n)
  if n % 6 == 2 then
    (2..n).step(2) + [3,1] + (7..n).step(2) + [5]
  elsif n % 6 == 3 then
    (4..n).step(2) + [2] + (5..n).step(2) + [1,3]
  else
    (2..n).step(2) + (1..n).step(2)
  end
end
