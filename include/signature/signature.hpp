#include "../cryptographic/cryptographic.hpp"
#include <array>
#include <fstream>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <vector>
#include <random>

class Signature {
public:
    static unsigned short hash_message(const std::string& message);

    std::pair<int, int> signWithElGamal(const std::string& filename);
    bool verifyWithElGamal(const std::string& filename, std::pair<int, int> keys);

    static std::pair<int, int> signWithRSA(const std::string& filename);
    static bool verifyWithRSA(const std::string& filename, std::pair<int, int> keys);

    static std::tuple<std::string, unsigned short, unsigned short> sign_documentGOST(unsigned int p, unsigned short q, unsigned int a, unsigned short x, const std::string& message);
    static bool verify_signatureGOST(unsigned int p, unsigned short q, unsigned int a, unsigned short y, const std::string& message, unsigned short r, unsigned short s);


    // static std::pair<EC_KEY*, EC_KEY*> generateGostKeys();
    // static std::vector<unsigned char> gostSign(EC_KEY* private_key, const std::string& data);
    // static bool gostVerify(EC_KEY* public_key, const std::vector<unsigned char>& signature, const std::string& data);

    


private:
    static long long hashFile(const std::string& filename);
    static void writeSignatureToFile(const std::string& filename, const long long signature);
    static long long readSignatureFromFile(const std::string& filename);
    static void writeSignatureToFileElGamal(const std::string& filename, const std::pair<long long, long long>& signature);
    static std::pair<long long, long long> readSignatureFromFileElGamal(const std::string& filename);
};