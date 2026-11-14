# Independent verification of OEIS A092506 — 2026-11-15

Source: 'iwasborninbali/oeis-A092506-unsubmitted' at '38169af9d7b0a6f5bedc1a538224214a20c673f8', provided archive. This report is an independent referee assessment, not an endorsement of any claim to priority.

## Claim

For every integer 'x >= 2', 'phi(x) + phi(x-1) = floor((3*x-2)/2)' if and only if 'x' is prime and 'x-1' is a power of 2 (including '1 = 2^0'); 'phi(1) = 1'.

This is the exact scope of 'CERTIFICATE.md' line 5. It does not settle whether additional Fermat primes exist.

## Proof check

**Verdict on 'proof.md': correct, with no mathematical gaps or conjectural dependencies.** I checked every substantive step, including the boundary cases.

- **Lines 1–3:** Statement and convention 'phi(1)=1' are consistent. The integer domain 'x >= 2' is explicit.
- **Line 5, first bound:** For 'm >= 2', 'phi(m) <= m-1'. Equality holds precisely for primes: for composite 'm', a proper divisor 'd' with '1 < d < m' is not coprime to 'm'. Correct.
- **Line 5, even bound:** If 'm' is even, every totative is odd, so 'phi(m) <= m/2'. When 'm' is a power of 2 all odd residues are coprime; otherwise 'm' has an odd prime factor 'p', which lies in '1..m-1' and witnesses strict inequality. Correct, including 'm=2'.
- **Line 7, 'x=2':** 'phi(2)+phi(1)=1+1=2=floor((6-2)/2)'. Correct.
- **Line 7, even 'x >= 4':** Apply 'phi(x) <= x/2' and 'phi(x-1) <= (x-1)-1=x-2', because 'x-1 >= 3'; then '3x/2-2 < 3x/2-1=floor((3x-2)/2)'. Correct: no even 'x >= 4' solves the equation.
- **Line 9, odd 'x >= 3':** Write 'm=x-1', even and at least 2. Integer arithmetic gives 'floor((3x-2)/2)=3m/2'. The upper bound 'phi(x)+phi(m) <= m + m/2' is tight if and only if **both** nonnegative deficits vanish. By line 5 this means 'x' prime and 'm' a power of 2. The converse follows by equality in both bounds. Correct.
- **Line 11, exponent restriction:** For prime '2^n+1', 'n >= 1', if 'n' is not a power of 2, write 'n=ab' with 'b>1' odd; then '2^a+1' is a proper factor of '(2^a)^b+1'. Correct. This is an ancillary reformulation, not a claim that the displayed list of Fermat primes is complete.

**Errors / unjustified steps / unstated mathematical assumptions / unproved conjectures:** **none**. **Fatal gaps:** none. **Fixable gaps:** none. Optional exposition only: add 'x-1 >= 3' in line 7 and 'p < m' in the even-bound argument; both are immediate from the stated hypotheses, not missing arguments.

The proof is elementary and human-checked here; it is not a formal proof-assistant certificate.

## Independent computation

**New program:** ['independent.cpp'](independent.cpp). Written from scratch for this audit, without importing or copying 'programs/producer.py' or 'verification/check.py'. It uses a **linear least-prime-factor sieve and the totient recurrence** 'phi(np)=p*phi(n)' when 'p | n', and 'phi(np)=(p-1)*phi(n)' otherwise; this differs from the producer's multiples-update totient sieve. For every 'x', primality is determined by 'least_prime[x] == x', and powers of two by an integer bit test. The program also recomputes 'phi' by individual gcd counts for '2 <= x <= 5000' as a check on the recurrence.

**Reproduction:** 'g++ -O3 -std=c++17 -Wall -Wextra -pedantic independent.cpp -o independent && ./independent 50000000' (the saved ['independent.log'](independent.log) includes '/usr/bin/time' wall time and peak RSS). Environment: GNU g++ 14.2.0, Linux container.

**Range:** every integer '2 <= x <= 50,000,000', inclusive, 50 times the producer's 1,000,000 and over 16,000 times the previous independent check's 3,000.

**Observed equation solutions:** '[2, 3, 5, 17, 257, 65537]'.

**Predicted solutions:** '[2, 3, 5, 17, 257, 65537]'.

**Results:** zero equation/prediction mismatches; zero mismatches in 'phi(n)=n-1 iff n prime'; zero violations of '2*phi(n) <= n' for even 'n'; zero mismatches in even equality iff 'n' is a power of 2; zero gcd-definition/recurrence mismatches through 5,000. Program output 'PASS'. 3,001,134 primes were found through 50 million.

**Runtime:** 0.98117 s measured internally (0.99 s wall, including the gcd prefix check); maximum resident set size 408,632 KiB.

**SHA-256** (exact UTF-8 bytes of local files, including trailing newlines):

- 'independent.cpp': 'ee0247de4501280e418334abf50fdaf8f6af73c53b5857a72a4cfb3c5fd6f775'
- 'independent.log': 'd0a45bff2a64af303e8ea9700ce1cf9dc68da4c9b564fd3b36052ffae6607e14'

Finite computation is a consistency check, not the basis for the universal theorem.

## Prior art

Search performed 2026-11-15. **Originality of the precise proof is not established by a non-exhaustive literature search**, even though no earlier proof of the *exact floor-sum equivalence* was found in the inspected sources. References, and what they do or do not establish:

1. [OEIS A092506](https://oeis.org/A092506) still calls the exact equality Benoit Cloitre's **conjecture**, dated March 2, 2018, rather than identifying a proof. [The public revision history](https://oeis.org/history?seq=A092506&start=40) shows Cloitre adding the conjecture in revision #44 on March 2, 2018. [More recent history](https://oeis.org/history?seq=A092506) (through revision #87 dated February 16, 2025) has no proof added. This supports that the explicit resolution has not been incorporated into the entry; it does not prove global priority.
2. [OEIS A171271](https://oeis.org/A171271) already states and proves: **a prime** 'p' satisfies 'phi(p)=2*phi(p-1)' iff 'p' is a Fermat prime. This is the **prime-only case**, not exclusion of composite solutions to Cloitre's floor-sum equality. [OEIS A019434](https://oeis.org/A019434/internal) also records the prime-only relationship. Prior mathematical ingredients are therefore not new.
3. [OEIS A239363](https://oeis.org/A239363) concerns the related **difference** equation 'phi(k+1)-phi(k)=k/2', noting Fermat-prime examples, but admits composites, and is not the sum equation. [OEIS A003401](https://oeis.org/A003401) is about totients that are powers of 2; relevant background, not this equivalence. [OEIS A019434](https://oeis.org/A019434/internal) defines Fermat primes, while [A092506](https://oeis.org/A092506) explicitly adds '2'.
4. [Rafay A. Ashary, *A Property of A092506*](https://oeis.org/A092506/a092506.pdf) (linked from the entry, 2016): independently characterizes A092506 via primitive roots modulo primes, **not** Cloitre's totient-sum equation. Read the one-page PDF, including its proof.
5. [Barry Brent, *On the constant terms of certain meromorphic modular forms for Hecke groups*](https://arxiv.org/abs/2212.12515) (2022): modular-forms/constant-term topic, not a proof of the displayed totient equation.
6. [Mathematics Stack Exchange: consecutive totients that are powers of two](https://math.stackexchange.com/questions/1886835/a-possible-property-of-eulers-totient-function-n-such-that-varphin-and) (2016) and [a discussion of sums of iterated totients](https://math.stackexchange.com/questions/4493160/superior-limit-of-sum-of-iterates-of-phi-n/4493192) (2022): related prime/inequality ideas, but neither addresses the precise equality. No exact proof was found in site-restricted Math Stack Exchange searches.
7. Site-restricted [MathOverflow](https://mathoverflow.net/) queries for consecutive totients, Fermat primes, and the exact expressions did not return the claim. Likewise, searches of [arXiv](https://arxiv.org/) and journal-indexed pages using 'A092506', 'Cloitre', '(phi(n)+phi(n-1))', the floor expression, and Fermat-prime combinations did not identify an exact proof or refutation. A related 2025 [journal paper on p-adic valuations of Euler's totient](https://doi.org/10.1007/s40840-025-01869-7) does not cover the sum equation.
8. [zbMATH Open](https://zbmath.org/) was searched via web-indexed queries ('A092506', totient/Fermat/consecutive); no matching exact result was returned. Direct access to the zbMATH search site failed in this environment, so **its holdings were not exhaustively checked**. The same non-exhaustiveness applies to journals and the two Q&A sites.

**Prior-art assessment:** the floor-sum *conjecture* is unquestionably pre-existing (Cloitre, 2018), and the prime case and requisite elementary bounds are pre-existing. I found no prior publication of the **composite-exclusion argument plus exact iff**; this is evidence of a newly documented resolution, **not proof that nobody previously obtained it**.

## Verdict

**COMPLETE for mathematical verification**: the exact universal claim is true; the supplied proof is correct with no gaps; all computational assertions were reproduced independently with stronger coverage (through 50,000,000). No counterexample was found.

**Novelty qualification:** the precise resolution does not appear in the OEIS material and literature inspected, but absolute priority/originality remains **not established** by this limited search. This verdict does not certify priority, machine-formalize the proof, or establish that there are no additional Fermat primes.
