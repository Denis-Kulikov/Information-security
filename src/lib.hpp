#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <ctime>
#include <tuple>
#include <fstream>

int gcd(int a, int b);
long long mod_pow(long long base, long long exp, long long mod);
int mod_inverse(int e, int phi);
bool is_prime(int n);
int generate_coprime(int phi);


class ShamirCipher {
public:
    static void gen_keys(int &e, int &d, int p) {
        int phi = p - 1;
        e = generate_coprime(phi);
        d = mod_inverse(e, phi);
    }

    static long long encrypt(long long message, int e, int p) {
        return mod_pow(message, e, p);
    }

    static long long decrypt(long long encrypted, int d, int p) {
        return mod_pow(encrypted, d, p);
    }
};

class ElGamalCipher {
public:
    static void gen_keys(long long &p, long long &g, long long &y, long long &x) {
        do {
            p = rand() % 100 + 100;
        } while (!is_prime(p));

        g = rand() % (p - 2) + 2;
        x = rand() % (p - 1) + 1;
        y = mod_pow(g, x, p);
    }

    static std::pair<long long, long long> encrypt(long long message, long long p, long long g, long long y) {
        long long k = rand() % (p - 1) + 1;
        long long a = mod_pow(g, k, p);
        long long b = (mod_pow(y, k, p) * message) % p;

        return {a, b};
    }

    static long long decrypt(long long a, long long b, long long p, long long x) {
        long long s = mod_pow(a, x, p);
        long long s_inv = mod_pow(s, p - 2, p);

        return (b * s_inv) % p;
    }
};

class VernamCipher {
public:
    static std::string gen_keys(int length) {
        std::string key;
        for (int i = 0; i < length; ++i) {
            key += char(rand() % 256);
        }
        return key;
    }

    static std::string encrypt_decrypt(const std::string &message, const std::string &key) {
        std::string result;
        for (size_t i = 0; i < message.length(); ++i) {
            result += message[i] ^ key[i];
        }
        return result;
    }
};

class RSA {
public:
    static void gen_keys(int &e, int &d, int &n) {
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

    static long long encrypt(long long mes, long long e, long long n) {
        return mod_pow(mes, e, n);
    }

    static long long decrypt(long long encrypted_mes, long long d, long long n) {
        return mod_pow(encrypted_mes, d, n);
    }
};