"""Independent direct gcd counts, OpenAI Codex, 2026-11-13."""
from math import gcd, isqrt
limit = 3000

def phi(n):
    return sum(gcd(n, j) == 1 for j in range(1, n + 1))

def prime(n):
    return n >= 2 and all(n % d for d in range(2, isqrt(n) + 1))

values = [0] + [phi(n) for n in range(1, limit + 1)]
solutions = [x for x in range(2, limit + 1) if values[x] + values[x - 1] == (3*x - 2)//2]
predicted = [x for x in range(2, limit + 1) if prime(x) and (x-1)&(x-2) == 0]
assert solutions == predicted
assert all((values[x] == x-1) == prime(x) for x in range(2, limit+1))
assert all(2*values[x] <= x and ((2*values[x] == x) == (x & (x-1) == 0)) for x in range(2, limit+1, 2))
print('range: 2..', limit)
print('equation solutions:', solutions)
print('predicted solutions:', predicted)
print('sets and both lemmas: PASS')
