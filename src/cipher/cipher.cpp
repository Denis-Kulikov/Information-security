#include <cipher/cipher.hpp>


void ShamirCipher::gen_keys(int &e, int &d, int p) {
    int phi = p - 1;
    e = generate_coprime(phi);
    d = mod_inverse(e, phi);
}

long long ShamirCipher::encrypt(long long message, int e, int p) {
    return mod_pow(message, e, p);
}

long long ShamirCipher::decrypt(long long encrypted, int d, int p) {
    return mod_pow(encrypted, d, p);
}

//

void ElGamalCipher::gen_keys(long long &p, long long &g, long long &y, long long &x) {
    do {
        p = rand() % 100 + 100;
    } while (!is_prime(p));

    g = rand() % (p - 2) + 2;
    x = rand() % (p - 1) + 1;
    y = mod_pow(g, x, p);
}

std::pair<long long, long long> ElGamalCipher::encrypt(long long message, long long p, long long g, long long y) {
    long long k = rand() % (p - 1) + 1;
    long long a = mod_pow(g, k, p);
    long long b = (mod_pow(y, k, p) * message) % p;

    return {a, b};
}

long long ElGamalCipher::decrypt(long long a, long long b, long long p, long long x) {
    long long s = mod_pow(a, x, p);
    long long s_inv = mod_pow(s, p - 2, p);

    return (b * s_inv) % p;
}

//

std::string VernamCipher::gen_keys(int length) {
    std::string key;
    for (int i = 0; i < length; ++i) {
        key += char(rand() % 256);
    }
    return key;
}

std::string VernamCipher::encrypt_decrypt(const std::string &message, const std::string &key) {
    std::string result;
    for (size_t i = 0; i < message.length(); ++i) {
        result += message[i] ^ key[i];
    }
    return result;
}

//

void RSA::gen_keys(int &e, int &d, int &n) {
    int p, q, phi;

    do {
        p = rand() % 100 + 100;
    } while (!is_prime(p));

    do {
        q = rand() % 100 + 100;
    } while (!is_prime(q));

    n = p * q;
    phi = (p - 1) * (q - 1);

    e = generate_coprime(phi);
    d = mod_inverse(e, phi);
}

long long RSA::encrypt(long long mes, long long e, long long n) {
    return mod_pow(mes, e, n);
}

long long RSA::decrypt(long long encrypted_mes, long long d, long long n) {
    return mod_pow(encrypted_mes, d, n);
}