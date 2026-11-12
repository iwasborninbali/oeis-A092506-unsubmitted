from math import isqrt

N = 1_000_000

# Euler's totient sieve
phi = list(range(N + 1))
for p in range(2, N + 1):
    if phi[p] == p:
        for m in range(p, N + 1, p):
            phi[m] -= phi[m] // p
phi[1] = 1

# Independent primality sieve
prime = bytearray([1]) * (N + 1)
prime[0:2] = b"\x00\x00"
for p in range(2, isqrt(N) + 1):
    if prime[p]:
        prime[p*p::p] = b"\x00" * (
            ((N - p*p) // p) + 1
        )

# Direct equation solutions
solutions = [
    x for x in range(2, N + 1)
    if phi[x] + phi[x-1] == (3*x - 2) // 2
]

# Independently predicted solutions
predicted = [
    x for x in range(2, N + 1)
    if prime[x] and (
        x == 2 or ((x-1) & (x-2)) == 0
    )
]

# Lemma 1
prime_lemma = all(
    (phi[n] == n-1) == bool(prime[n])
    for n in range(2, N + 1)
)

# Lemma 2
even_lemma = all(
    2*phi[n] <= n
    and ((2*phi[n] == n) == ((n & (n-1)) == 0))
    for n in range(2, N + 1, 2)
)

print(f"range: 2..{N}")
print(f"equation solutions: {solutions}")
print(f"predicted solutions: {predicted}")
print(f"all solution sets agree: {solutions == predicted}")
print(f"prime lemma: {prime_lemma}")
print(f"even lemma: {even_lemma}")
