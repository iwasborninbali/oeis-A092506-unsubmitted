# Proof

For every integer x >= 2, phi(x)+phi(x-1)=floor((3x-2)/2) if and only if x is a prime of the form 2^n+1, n >= 0. Here phi(1)=1.

For m >= 2, phi(m) <= m-1, with equality exactly when m is prime: if m is prime every number from 1 to m-1 is coprime to m; if composite, a proper divisor is not. For even m >= 2, phi(m) <= m/2, with equality exactly when m is a power of 2: only odd integers can be coprime to m, and all are coprime if m is a power of 2. Otherwise an odd prime divisor of m is among the odd integers but is not coprime to m.

At x=2, both sides equal 2. For even x >= 4, the two bounds give phi(x)+phi(x-1) <= x/2+x-2 = 3x/2-2, strictly less than the right side 3x/2-1.

For odd x >= 3, put m=x-1. The right side equals 3m/2, while phi(x)+phi(m) <= m+m/2. Equality holds exactly when both constituent inequalities are equalities, namely when x is prime and m is a power of 2. Conversely those conditions give equality. With x=2 included, this proves the equivalence.

For n >= 1, a prime 2^n+1 has n a power of 2: otherwise n=ab with odd b>1, and 2^a+1 is a proper divisor of (2^a)^b+1. The argument does not assert that the currently displayed Fermat primes are the only ones. This proof is human-checkable and is not formally machine-checked.
