#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <ctime>
#include <tuple>
#include <fstream>
#include "lib.hpp"


void Shamir_test(const std::string& input_file) {
    std::string Shamir_file = input_file;
    std::string Shamir_encrypted_file = "data/Shamir_encrypted.bin";
    std::string Shamir_decrypted_file = "data/Shamir_decrypted.txt";

    int p = 30803;
    int eA, dA, eB, dB;

    ShamirCipher::gen_keys(eA, dA, p);
    ShamirCipher::gen_keys(eB, dB, p);

    std::ifstream infile(Shamir_file, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Unable to open input file for Shamir!" << std::endl;
        return;
    }

    std::string message((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    std::ofstream encrypted_out(Shamir_encrypted_file, std::ios::binary);
    for (char c : message) {
        long long encrypted_char = ShamirCipher::encrypt(ShamirCipher::encrypt(c, eA, p), eB, p);
        encrypted_out.write(reinterpret_cast<const char*>(&encrypted_char), sizeof(encrypted_char));
    }
    encrypted_out.close();

    std::ifstream encrypted_in(Shamir_encrypted_file, std::ios::binary);
    std::ofstream decrypted_out(Shamir_decrypted_file, std::ios::binary);
    long long encrypted_char;
    while (encrypted_in.read(reinterpret_cast<char*>(&encrypted_char), sizeof(encrypted_char))) {
        char decrypted_char = static_cast<char>(ShamirCipher::decrypt(ShamirCipher::decrypt(encrypted_char, dB, p), dA, p));
        decrypted_out.put(decrypted_char);
    }
    encrypted_in.close();
    decrypted_out.close();
}


void ElGamal_test(const std::string& input_file) {
    std::string ElGamal_file = input_file;
    std::string ElGamal_encrypted_file = "data/ElGamal_encrypted.bin";
    std::string ElGamal_decrypted_file = "data/ElGamal_decrypted.txt";

    long long p, g, y, x;
    ElGamalCipher::gen_keys(p, g, y, x);

    std::ifstream infile(ElGamal_file, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Unable to open input file for ElGamal!" << std::endl;
        return;
    }

    std::string message((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    std::ofstream encrypted_out(ElGamal_encrypted_file, std::ios::binary);
    for (char c : message) {
        auto encrypted_pair = ElGamalCipher::encrypt(c, p, g, y);
        encrypted_out.write(reinterpret_cast<const char*>(&encrypted_pair.first), sizeof(encrypted_pair.first));
        encrypted_out.write(reinterpret_cast<const char*>(&encrypted_pair.second), sizeof(encrypted_pair.second));
    }
    encrypted_out.close();

    std::ifstream encrypted_in(ElGamal_encrypted_file, std::ios::binary);
    std::ofstream decrypted_out(ElGamal_decrypted_file, std::ios::binary);
    long long a, b;
    while (encrypted_in.read(reinterpret_cast<char*>(&a), sizeof(a)) &&
           encrypted_in.read(reinterpret_cast<char*>(&b), sizeof(b))) {
        char decrypted_char = static_cast<char>(ElGamalCipher::decrypt(a, b, p, x));
        decrypted_out.put(decrypted_char);
    }
    encrypted_in.close();
    decrypted_out.close();
}

void Vernam_test(const std::string& input_file) {
    std::string Vernam_file = input_file;
    std::string Vernam_encrypted_file = "data/Vernam_encrypted.bin";
    std::string Vernam_decrypted_file = "data/Vernam_decrypted.txt";

    std::ifstream infile(Vernam_file, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Unable to open input file for Vernam!" << std::endl;
        return;
    }

    std::string message((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    std::string key = VernamCipher::gen_keys(message.size());

    std::ofstream encrypted_out(Vernam_encrypted_file, std::ios::binary);
    std::string encrypted_message = VernamCipher::encrypt_decrypt(message, key);
    encrypted_out.write(encrypted_message.c_str(), encrypted_message.size());
    encrypted_out.close();

    std::ofstream decrypted_out(Vernam_decrypted_file, std::ios::binary);
    std::string decrypted_message = VernamCipher::encrypt_decrypt(encrypted_message, key);
    decrypted_out.write(decrypted_message.c_str(), decrypted_message.size());
    decrypted_out.close();
}

void RSA_test(const std::string& input_file) {
    std::string RSA_file = input_file;
    std::string RSA_encrypted_file = "data/RSA_encrypted.bin";
    std::string RSA_decrypted_file = "data/RSA_decrypted.txt";

    int e, d, n;
    RSA::gen_keys(e, d, n);

    std::ifstream infile(RSA_file, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Unable to open input file for RSA!" << std::endl;
        return;
    }

    std::string message((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    std::ofstream encrypted_out(RSA_encrypted_file, std::ios::binary);
    for (char c : message) {
        long long encrypted_char = RSA::encrypt(c, e, n);
        encrypted_out.write(reinterpret_cast<const char*>(&encrypted_char), sizeof(encrypted_char));
    }
    encrypted_out.close();

    std::ifstream encrypted_in(RSA_encrypted_file, std::ios::binary);
    std::ofstream decrypted_out(RSA_decrypted_file, std::ios::binary);
    long long encrypted_char;
    while (encrypted_in.read(reinterpret_cast<char*>(&encrypted_char), sizeof(encrypted_char))) {
        char decrypted_char = static_cast<char>(RSA::decrypt(encrypted_char, d, n));
        decrypted_out.put(decrypted_char);
    }
    encrypted_in.close();
    decrypted_out.close();
}
