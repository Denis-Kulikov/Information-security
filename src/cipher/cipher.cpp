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

void RSACipher    ::gen_keys(int &e, int &d, int &n) {
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

long long RSACipher    ::encrypt(long long mes, long long e, long long n) {
    return mod_exp(mes, e, n);
}

long long RSACipher    ::decrypt(long long encrypted_mes, long long d, long long n) {
    return mod_exp(encrypted_mes, d, n);
}

//

// 𝑁 = 𝑃𝑄, 𝑁 ≥ 10^9.  верхней границей для числа 𝑁 будет 2 × 10^9.  32500 ≤ 𝑃,𝑄 ≤ 45000. 
// void GOSTCipher::gen_keys(long long &p, long long &q, long long &g, long long &y, long long &x) {
//     do {
//         p = rand() % (45000 - 32500) + 32500;
//     } while (!is_prime(p));

//     do {
//         q = rand() % (45000 - 32500) + 32500;
//     } while (!is_prime(q));

//     g = 2;
        
//     // x = generate_private_key(q);
//     x = 1 + rand() % (q - 1); // Приватный ключ x
//     y = mod_exp(g, x, p);     // Открытый ключ y
// }

// long long GOSTCipher::encrypt(long long message, long long e, long long N) {
//     return mod_exp(message, e, N);
// }

// long long GOSTCipher::decrypt(long long encrypted_message, long long d, long long N) {
//     return mod_exp(encrypted_message, d, N);
// }