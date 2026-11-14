// Independent verifier of the A092506 totient identity.
// Uses a linear least-prime-factor/totient recurrence, unlike the
// repository's divisor-multiple totient sieve or direct gcd check.
// Compile: g++ -O3 -std=c++17 -Wall -Wextra -pedantic independent.cpp -o independent
// Run: ./independent 50000000
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

static bool power_of_two(std::uint32_t z) {
    return z && ((z & (z - 1)) == 0);
}

int main(int argc, char** argv) {
    using namespace std;
    using Clock = chrono::steady_clock;
    const auto t0 = Clock::now();
    const uint32_t limit = argc > 1 ? static_cast<uint32_t>(stoul(argv[1])) : 50000000U;
    if (limit < 2 || limit > 100000000U) {
        cerr << "Limit must lie between 2 and 100000000\n";
        return 2;
    }

    vector<uint32_t> least_prime(limit + 1, 0);
    vector<uint32_t> totient(limit + 1, 0);
    vector<uint32_t> primes;
    totient[1] = 1;

    for (uint32_t n = 2; n <= limit; ++n) {
        if (least_prime[n] == 0) {
            least_prime[n] = n;
            totient[n] = n - 1;
            primes.push_back(n);
        }
        for (uint32_t p : primes) {
            uint64_t k = static_cast<uint64_t>(p) * n;
            if (k > limit || p > least_prime[n]) break;
            least_prime[k] = p;
            if (p == least_prime[n]) {
                totient[k] = totient[n] * p;
                break;
            }
            totient[k] = totient[n] * (p - 1);
        }
    }
    auto t1 = Clock::now();

    vector<uint32_t> found, expected;
    uint64_t equation_disagreements = 0, prime_lemma_disagreements = 0;
    uint64_t even_bound_disagreements = 0, even_equality_disagreements = 0;
    uint64_t direct_gcd_disagreements = 0;
    for (uint32_t x = 2; x <= limit; ++x) {
        bool equation = (uint64_t(totient[x]) + totient[x - 1] == (3ULL * x - 2) / 2);
        bool is_prime = least_prime[x] == x;
        bool prediction = is_prime && power_of_two(x - 1);
        if (equation) found.push_back(x);
        if (prediction) expected.push_back(x);
        equation_disagreements += equation != prediction;
        prime_lemma_disagreements += ((totient[x] == x - 1) != is_prime);
        if ((x & 1U) == 0) {
            even_bound_disagreements += (2ULL * totient[x] > x);
            even_equality_disagreements += ((2ULL * totient[x] == x) != power_of_two(x));
        }
        // A completely separate totient definition for a short prefix.
        // This checks against the trivial/gcd method without using repository code.
        if (x <= 5000) {
            uint32_t count = 0;
            for (uint32_t y = 1; y <= x; ++y) count += (std::gcd(x, y) == 1);
            direct_gcd_disagreements += (count != totient[x]);
        }
    }
    auto t2 = Clock::now();

    auto print_vec = [](const char* name, const vector<uint32_t>& values) {
        cout << name << ": [";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i) cout << ", ";
            cout << values[i];
        }
        cout << "]\n";
    };
    cout << "range: 2.." << limit << " (inclusive)\n";
    cout << "method: linear least-prime-factor recurrence for phi, full-range equation/lemma checks, gcd counts through 5000\n";
    cout << "prime count: " << primes.size() << "\n";
    print_vec("equation solutions", found);
    print_vec("predicted solutions", expected);
    cout << "equation/prediction mismatches: " << equation_disagreements << "\n";
    cout << "prime-bound equality mismatches: " << prime_lemma_disagreements << "\n";
    cout << "even-bound violations: " << even_bound_disagreements << "\n";
    cout << "even-bound equality mismatches: " << even_equality_disagreements << "\n";
    cout << "gcd-definition/recurrence mismatches (2..5000): " << direct_gcd_disagreements << "\n";
    cout << "sieve seconds: " << chrono::duration<double>(t1 - t0).count() << "\n";
    cout << "test seconds: " << chrono::duration<double>(t2 - t1).count() << "\n";
    cout << "total seconds: " << chrono::duration<double>(t2 - t0).count() << "\n";
    bool ok = !equation_disagreements && !prime_lemma_disagreements &&
              !even_bound_disagreements && !even_equality_disagreements &&
              !direct_gcd_disagreements;
    cout << "verdict: " << (ok ? "PASS" : "FAIL") << "\n";
    return ok ? 0 : 1;
}
