#include <cipher/cipher.hpp>
#include <signature/signature.hpp>

#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <cassert>

unsigned short hash_message(const std::string& message) {
    unsigned int hash_value = 0;
    for (char c : message) {
        hash_value = (hash_value * 31 + c) % 65536; // Простейший хэш (мод 65536 для 16 бит)
    }
    return hash_value; // Возвращаем значение хэша в пределах 16 бит
}



std::tuple<std::string, unsigned short, unsigned short> sign_document(unsigned int p, unsigned short q, unsigned int a, unsigned short x, const std::string& message) {
    unsigned short h = hash_message(message);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, q - 1);
    unsigned short k = dis(gen);

    unsigned short r = mod_exp(a, k, p) % q;
    if (r == 0)
        return sign_document(p, q, a, x, message);

    unsigned short s = (k * h + x * r) % q;
    if (s == 0)
        return sign_document(p, q, a, x, message);

    return {message, r, s};
}

bool verify_signature(unsigned int p, unsigned short q, unsigned int a, unsigned short y, const std::string& message, unsigned short r, unsigned short s) {
    unsigned short h = hash_message(message);

    if (!(0 < r && r < q)) {
        return false;
    }

    unsigned short h_inv = mod_inverse(h, q);
    unsigned short u1 = (s * h_inv) % q;
    unsigned short u2 = (-r * h_inv) % q;

    unsigned short v = (mod_exp(a, u1, p) * mod_exp(y, u2, p)) % p % q;

    return v == r;
}


int main() {
    srand(time(0));
    std::string file_name = "test";
    
    if (Signature::verifyWithRSA(file_name, Signature::signWithRSA(file_name))) {
        std::cout << "Подпись " "Эль-Гамаля" " произошла успешно." << std::endl;
    } else {
        std::cout << "Подпись " "Эль-Гамаля" " произошла с ошибками." << std::endl;
    }

    if (Signature::verifyWithRSA(file_name, Signature::signWithRSA(file_name))) {
        std::cout << "Подпись " "RSA" " произошла успешно." << std::endl;
    } else {
        std::cout << "Подпись " "RSA" " произошла с ошибками." << std::endl;
    }

    // auto keys = Signature::generateGostKeys();
    // std::string message = "Test GOST";
    // auto signature = Signature::gostSign(keys.first, message);
    // if (Signature::gostVerify(keys.second, signature, message)) {
    //     std::cout << "Подпись " "ГОСТ" " произошла успешно." << std::endl;
    // } else {
    //     std::cout << "Подпись " "ГОСТ" " произошла с ошибками." << std::endl;
    // }



    unsigned int p = 2147483647;  // p размером 31 бит (пример простого числа)
    unsigned short q = 65535;      // q размером 16 бит (максимальное значение для 16 бит)
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, p - 1);
    unsigned int g = dis(gen);
    unsigned int b = dis(gen) % 1000;
    unsigned int a = mod_exp(g, b, p);

    std::uniform_int_distribution<> dis_x(1, q - 1);
    unsigned short x = dis_x(gen);

    unsigned short y = mod_exp(a, x, p);

    bool valid;
    do {
        std::string message = "Документ для подписи";
        auto [signed_message, r, s] = sign_document(p, q, a, x, message);
        valid = verify_signature(p, q, a, y, signed_message, r, s);
    } while (!valid);


    if (valid) {
        std::cout << "Подпись " "ГОСТ" " произошла успешно." << std::endl;
    } else {
        std::cout << "Подпись " "ГОСТ" " произошла с ошибками." << std::endl;
    }


    return 0;
}
