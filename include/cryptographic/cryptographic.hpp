#include <iostream>
#include <cmath>
#include <cstdlib>

int gcd(int a, int b);
long long mod_exp(long long base, long long exp, long long mod);
int mod_inverse(int e, int phi);
unsigned short umod_inverse(unsigned short a, unsigned short m);
bool is_prime(int n);
int generate_coprime(int phi);