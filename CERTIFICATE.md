# Verification certificate

## Claim

For every integer x >= 2, phi(x)+phi(x-1)=floor((3x-2)/2) if and only if x is prime and x-1 is a power of 2 (including 1).

## Evidence

| What | Program | Author and date | Coverage | Result |
|---|---|---|---|---|
| Human-checkable proof | `proof.md` | Adapted by OpenAI Codex from ChatGPT's 2026-11-12 answer | All x >= 2 | Not machine-checked |
| Producer | `programs/producer.py` | ChatGPT, 2026-11-12 | Sieve and lemmas through 1,000,000 | Passed |
| Independent check | `verification/check.py` | OpenAI Codex, 2026-11-13 | Direct gcd counts and trial primality through 3000 | Passed |
| Independent referee and check | `verification/agent-2026-11-15/` (REPORT.md, independent.cpp) | ChatGPT agent, 2026-11-15; wrote its own C++ from scratch, no repository code | Every x from 2 to 50,000,000: the equation and both totient bounds; proof read line by line | Passed; proof correct, no gaps |

The checker shares no producer code or tables; both use the same equation and conditions. Guide review is recorded in `athanor-oeis/tasks/README.md`.

## Replayed for this repository

2026-11-13, Darwin arm64, Python 3.14.6: `python3 programs/producer.py` reports solutions `[2, 3, 5, 17, 257, 65537]`, equality and both lemmas true through 1,000,000. `python3 verification/check.py` reports `[2, 3, 5, 17, 257]` and `sets and both lemmas: PASS` through 3000. Full outputs are in `verification/logs/`.

2026-11-15, Darwin arm64 (Apple clang, `-O3 -std=c++17`), by the guide: `./independent 50000000` from
`verification/agent-2026-11-15/` reports `verdict: PASS` in 1.03 s, the same result as the agent's log.

## Not covered

The proof is not machine-checked. The separate program covers only 3000, not the producer's full million. The existence of further Fermat primes is not resolved. The source review's separate 10^7 sieve was not replayed.

## Guide's independent check

15 November 2026: the guide read `proof.md` line by line. Both bounds are correct: phi(m) <= m-1 for m >= 2 with
equality exactly for primes; phi(m) <= m/2 for even m with equality exactly for powers of 2 (an odd prime divisor of a
non-power of 2 is an odd number in 1..m that is not coprime to m). For even x >= 4 the sum is at most 3x/2-2, below the
right side 3x/2-1. For odd x >= 3, with m = x-1 even, the right side is floor((3m+1)/2) = 3m/2 and the sum is at most
m + m/2, with equality exactly when both bounds are equalities. x = 2 gives 2 = 2. The closing remark (2^n+1 prime
implies n is a power of 2) is standard and not needed for the equivalence. Verdict: the proof is correct and complete.
The guide also replayed the agent's independent program (above).

## Verdict

complete — the universal claim is proved by an elementary argument read independently by the guide and by a separate
referee; every computational statement is checked by two programs that share no code (through 1,000,000 and
50,000,000). Not covered: no formal (machine) proof; the priority search is not exhaustive (see PRIOR-ART.md).
