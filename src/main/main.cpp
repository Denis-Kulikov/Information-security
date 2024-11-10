#include <cipher/cipher.hpp>


int main() {
    srand(time(0));

    std::string input_file = "input.txt";


    #if true
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
