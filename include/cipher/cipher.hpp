#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <tuple>
#include <fstream>
#include <vector>
#include "../cryptographic/cryptographic.hpp"
    // std::cout << "hash: " << h << std::endl;


class ShamirCipher {
public:
    static void gen_keys(int &e, int &d, int p);
    static long long encrypt(long long message, int e, int p);
    static long long decrypt(long long encrypted, int d, int p);
};

class ElGamalCipher {
public:
    static void gen_keys(long long &p, long long &g, long long &y, long long &x);
    static std::pair<long long, long long> encrypt(long long message, long long p, long long g, long long y);
    static long long decrypt(long long a, long long b, long long p, long long x);
};

class VernamCipher {
public:
    static std::string gen_keys(int length);
    static std::string encrypt_decrypt(const std::string &message, const std::string &key);
};

class RSACipher {
public:
    static void gen_keys(int &e, int &d, int &n);
    static long long encrypt(long long mes, long long e, long long n);
    static long long decrypt(long long encrypted_mes, long long d, long long n);
};

// class GOSTCipher {
// public:
//     static void gen_keys(long long &p, long long &q, long long &g, long long &y, long long &x);
//     static long long encrypt(long long message, long long e, long long N);
//     static long long decrypt(long long encrypted_message, long long d, long long N);
// };
