#include <cipher/cipher.hpp>


void ShamirCipher::gen_keys(int &e, int &d, int p) {
    int phi = p - 1;
    e = generate_coprime(phi);
    d = mod_inverse(e, phi);
}

long long ShamirCipher::encrypt(long long message, int e, int p) {
    return mod_exp(message, e, p);
}

long long ShamirCipher::decrypt(long long encrypted, int d, int p) {
    return mod_exp(encrypted, d, p);
}

//

void ElGamalCipher::gen_keys(long long &p, long long &g, long long &y, long long &x) {
    do {
        p = rand() % 100 + 100;
    } while (!is_prime(p));

    g = rand() % (p - 2) + 2;
    x = rand() % (p - 1) + 1;
    y = mod_exp(g, x, p);
}

std::pair<long long, long long> ElGamalCipher::encrypt(long long message, long long p, long long g, long long y) {
    long long k = rand() % (p - 1) + 1;
    long long a = mod_exp(g, k, p);
    long long b = (mod_exp(y, k, p) * message) % p;

    return {a, b};
}

long long ElGamalCipher::decrypt(long long a, long long b, long long p, long long x) {
    long long s = mod_exp(a, x, p);
    long long s_inv = mod_exp(s, p - 2, p);

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

void RSACipher::gen_keys(long long &e, long long &d, long long &n) {
    long long p, q, phi;

    const int N = 100;

    do {
        p = rand() % N + N;
    } while (!is_prime(p));

    do {
        q = rand() % N + N;
    } while (!is_prime(q));

    n = p * q;
    phi = (p - 1) * (q - 1);

    e = generate_coprime(phi);
    d = mod_inverse(e, phi);
}


void RSACipher::gen_keys(long long *e, long long *d, long long *n, long long p, long long q, int number) {
    long long shared_n =  p * q;
    long long phi = (p - 1) * (q - 1);

    for (int i = 0; i < number; ++i) {
        n[i] = shared_n;
        e[i] = generate_coprime(phi);
        d[i] = mod_inverse(e[i], phi);
    }
}

long long RSACipher::encrypt(long long mes, long long e, long long n) {
    return mod_exp(mes, e, n);
}

long long RSACipher::decrypt(const long long encrypted_mes, const long long d, const long long n) {
    return mod_exp(encrypted_mes, d, n);
}
