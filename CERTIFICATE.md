# Verification certificate

## Claim

For every integer x >= 2, phi(x)+phi(x-1)=floor((3x-2)/2) if and only if x is prime and x-1 is a power of 2 (including 1).

## Evidence

| What | Program | Author and date | Coverage | Result |
|---|---|---|---|---|
| Human-checkable proof | `proof.md` | Adapted by OpenAI Codex from ChatGPT's 2026-11-12 answer | All x >= 2 | Not machine-checked |
| Producer | `programs/producer.py` | ChatGPT, 2026-11-12 | Sieve and lemmas through 1,000,000 | Passed |
| Independent check | `verification/check.py` | OpenAI Codex, 2026-11-13 | Direct gcd counts and trial primality through 3000 | Passed |

The checker shares no producer code or tables; both use the same equation and conditions. Guide review is recorded in `athanor-oeis/tasks/README.md`.

## Replayed for this repository

2026-11-13, Darwin arm64, Python 3.14.6: `python3 programs/producer.py` reports solutions `[2, 3, 5, 17, 257, 65537]`, equality and both lemmas true through 1,000,000. `python3 verification/check.py` reports `[2, 3, 5, 17, 257]` and `sets and both lemmas: PASS` through 3000. Full outputs are in `verification/logs/`.

## Not covered

The proof is not machine-checked. The separate program covers only 3000, not the producer's full million. The existence of further Fermat primes is not resolved. The source review's separate 10^7 sieve was not replayed.

## Guide's independent check

pending

## Verdict

partial — the independent finite computation covers only 3000 of the producer's 1,000,000 cases; the universal proof has not been formally checked.
