# OEIS A092506: totient equation (not yet submitted)

<!-- oeis-status:begin -->
**OEIS status: not submitted** (lab registry, 15 Nov 2026).

- [A092506](https://oeis.org/A092506), Cloitre's conjecture proved (iff x = 2 or a Fermat prime): **verified** (2026-11-15: certificate complete: guide's proof reading, independent referee and C++ check to 5e7, prior-art search (15 Nov 2026)). Certificate: complete.

Rules and the full registry: [athanor-oeis](https://github.com/iwasborninbali/athanor-oeis/blob/main/REGISTRY.md).
<!-- oeis-status:end -->

## Definition

A092506 lists the primes of the form 2^n+1 for integers n >= 0, in increasing order, with offset 1. The empty exponent case n=0 gives 2. Euler's totient has phi(1)=1. The task's `context/A092506.seq` and the live [entry](https://oeis.org/A092506), read 2026-11-13, give Benoit Cloitre's March 2, 2018 conjecture: “Conjecture: these are the only solutions to the equation A000010(x)+A000010(x-1)=floor((3x-2)/2).” The live entry does not record its proof.

## Terms / result

For integers x >= 2, the equation holds if and only if x is a prime 2^n+1, n >= 0. This proves the characterization of the sequence, without asserting that the displayed list is complete.

| Index | Known term |
|---:|---:|
| 1 | 2 |
| 2 | 3 |
| 3 | 5 |
| 4 | 17 |
| 5 | 257 |
| 6 | 65537 |

## How it was obtained

The reviewed proof applies sharp bounds for phi on arbitrary and even integers, with separate cases for x=2 and the parity of x. The complete argument is in [proof.md](proof.md).

## Verification

A sieve was replayed through one million and an independently written direct gcd-count check through 3000. The proof is human-checkable, not machine-checked; no finite check establishes it for all x. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

Cloitre stated the conjecture; the prime-case relationship was already recorded in A171271 and A019434. ChatGPT gave the reviewed proof; Claude Code reviewed it. See [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Run `python3 programs/producer.py` and `python3 verification/check.py` (each about a second on the recorded machine). Each prints equal predicted and actual solution sets and successful lemma checks; the former ends `even lemma: True`, the latter `sets and both lemmas: PASS`. Outputs are in `verification/logs/`.

## Provenance

Source `projects/science/athanor-oeis`, commit `7662d9a678c6d414685a899a631c63ac320f6840`, `tasks/2026-11-12-A092506-totient-equation/answers/2026-11-12-chatgpt.md`, `context/A092506.seq`, and `TASK.md`. Guide review is recorded in `tasks/README.md`.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
