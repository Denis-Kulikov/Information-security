#include "lib.hpp"

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

#include "test.cpp"

int main() {
    srand(time(0));

    std::string input_file = "input.txt";

    Shamir_test(input_file);
    ElGamal_test(input_file);
    Vernam_test(input_file);
    RSA_test(input_file);


    #if false
    int p = 30803;

    int eA, dA;
    ShamirCipher::gen_keys(eA, dA, p);
    std::cout << "Alice's keys: (eA = " << eA << ", dA = " << dA << ")\n";

    int eB, dB;
    ShamirCipher::gen_keys(eB, dB, p);
    std::cout << "Bob's keys: (eB = " << eB << ", dB = " << dB << ")\n";

    long long message;
    std::cout << "Enter message to encrypt (as a number): ";
    std::cin >> message;

    long long encrypted_by_Alice = ShamirCipher::encrypt(message, eA, p);
    std::cout << "Message after Alice encryption: " << encrypted_by_Alice << "\n";

    long long encrypted_by_Bob = ShamirCipher::encrypt(encrypted_by_Alice, eB, p);
    std::cout << "Message after Bob encryption: " << encrypted_by_Bob << "\n";

    long long decrypted_by_Bob = ShamirCipher::decrypt(encrypted_by_Bob, dB, p);
    std::cout << "Message after Bob decryption: " << decrypted_by_Bob << "\n";

    long long decrypted_by_Alice = ShamirCipher::decrypt(decrypted_by_Bob, dA, p);
    std::cout << "Message after Alice decryption: " << decrypted_by_Alice << "\n";
    #endif

    #if false
    long long p, g, y, x;
    ElGamalCipher::gen_keys(p, g, y, x);

    std::cout << "Public key: (p = " << p << ", g = " << g << ", y = " << y << ")\n";
    std::cout << "Private key: (x = " << x << ")\n";

    long long message;
    std::cout << "Enter message to encrypt (as a number): ";
    std::cin >> message;

    auto encrypted_message = ElGamalCipher::encrypt(message, p, g, y);
    std::cout << "Encrypted message: (a = " << encrypted_message.first << ", b = " << encrypted_message.second << ")\n";

    long long decrypted_message = ElGamalCipher::decrypt(encrypted_message.first, encrypted_message.second, p, x);
    std::cout << "Decrypted message: " << decrypted_message << "\n";
    #endif

    #if false
    std::string message;
    std::cout << "Enter message to encrypt: ";
    std::getline(std::cin, message);

    std::string key = VernamCipher::gen_keys(message.length());
    std::cout << "Generated key: " << key << "\n";

    std::string encrypted_message = VernamCipher::encrypt_decrypt(message, key);
    std::cout << "Encrypted message: " << encrypted_message << "\n";

    std::string decrypted_message = VernamCipher::encrypt_decrypt(encrypted_message, key);
    std::cout << "Decrypted message: " << decrypted_message << "\n";
    #endif

    #if false
    int e, d, n;
    RSA::gen_keys(e, d, n);

    std::cout << "Public key: (" << e << ", " << n << ")\n";
    std::cout << "Private key: (" << d << ", " << n << ")\n";

    long long message;
    std::cout << "Enter message to encrypt (as a number): ";
    std::cin >> message;

    long long encrypted_message = RSA::encrypt(message, e, n);
    std::cout << "Encrypted message: " << encrypted_message << "\n";

    long long decrypted_message = RSA::decrypt(encrypted_message, d, n);
    std::cout << "Decrypted message: " << decrypted_message << "\n";
    #endif

    return 0;
}
