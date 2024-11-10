#include <cryptographic/cryptographic.hpp>


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int mod_inverse(int e, int phi) {
    int t = 0, new_t = 1;
    int r = phi, new_r = e;

    while (new_r != 0) {
        int quotient = r / new_r;
        std::tie(t, new_t) = std::make_pair(new_t, t - quotient * new_t);
        std::tie(r, new_r) = std::make_pair(new_r, r - quotient * new_r);
    }

    if (r > 1) return -1;
    if (t < 0) t += phi;
    return t;
}

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int generate_coprime(int phi) {
    int e;
    do {
        e = rand() % phi;
    } while (gcd(e, phi) != 1);
    return e;
}
