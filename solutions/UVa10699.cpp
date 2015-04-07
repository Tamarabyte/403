/* UVa problem: 10699 - CountTheFactors
 *
 * Topic: Number Theory
 *
 * Level: trivial
 *
 * Brief problem description:
 *  Given the number count the different prime factors of that number.
 *
 * Solution Summary:
 *  The maximum size is small enough that we can use a sieve to precompute primes
 *  and then iterate through primes checking divisibility.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 *
 * Language: C++11
 */

#include <cstdio>
#include <bitset>
#include <vector>

using namespace std;
typedef long long ll;

ll sieve_size;
bitset<10000001> bits;
vector<int> primes;


// sieve implementation referenced from
// Competitive Programming 3
void sieve(ll upper) {
    sieve_size = upper + 1;
    bits.set();

    for (ll i = 2; i <= sieve_size; ++i) {

        // if i is already crossed out then continue
        if (!bits[i])
            continue;

        // cross out multiples of i
        for (ll j = i*i; j <= sieve_size; j +=i)
            bits[j] = 0;

        primes.push_back((int)i);
    }
}

bool is_prime(ll num) {

    // retrieve from sieve if possible
    if (num <= sieve_size)
        return bits[num];

    // otherwise use the sieve to calculate
    for (int i = 0; i < (int)primes.size(); i++) {
        if (num % primes[i] == 0)
            return false;
    }

    return true;
}

// referenced from Competitive Programming 3
ll count_prime_factors(ll n) {
    int i = 0, counts = 0;
    ll prime_factor = primes[i];

    while (prime_factor * prime_factor <= n) {
        if (n % prime_factor == 0)
            counts++;

        while (n % prime_factor == 0)
            n /= prime_factor;

        prime_factor = primes[++i];
    }

    if (n != 1)
        ++counts;

    return counts;
}

int main() {
    primes.clear();
    sieve(1000000);

    int num;
    while(scanf("%d", &num), num) {

        printf("%d : %lld\n", num, count_prime_factors(num));
    }


}
