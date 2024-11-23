#include <signature/signature.hpp>
#include <cipher/cipher.hpp>


unsigned short Signature::hash_message(const std::string& message) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, message.c_str(), message.size());
    SHA256_Final(hash, &sha256_ctx);
    
    unsigned short hash_value = (hash[0] << 8) | hash[1];
    return hash_value;
}

long long str_to_ll(std::vector<unsigned char> &str)
{
    long long hash_value = 0;
    for (auto it = str.rbegin(); it < str.rend(); ++it) {
        hash_value += *it;
    }
    return hash_value;
}

long long Signature::hashFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for hashing.");
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    std::vector<unsigned char> buffer(1024);
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);

    while (file.good()) {
        file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        SHA256_Update(&sha256, buffer.data(), file.gcount());
    }

    SHA256_Final(hash.data(), &sha256);

    return str_to_ll(hash);
}

void Signature::writeSignatureToFile(const std::string& filename, const long long signature) {
    std::ofstream outFile(filename + "-signed.sig", std::ios::binary);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file to save signature.");
    }
    outFile.write(reinterpret_cast<const char*>(&signature), sizeof(signature));
    outFile.close();
}


long long Signature::readSignatureFromFile(const std::string& filename) {
    std::ifstream inFile(filename + "-signed.sig", std::ios::binary);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open signature file.");
    }

    long long signature;
    inFile.read(reinterpret_cast<char*>(&signature), sizeof(signature));
    inFile.close();

    return signature;
}

void Signature::writeSignatureToFileElGamal(const std::string& filename, const std::pair<long long, long long>& signature) {
    std::ofstream outFile(filename + "-signed.sig", std::ios::binary);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file to save signature.");
    }
    outFile.write(reinterpret_cast<const char*>(&signature.first), sizeof(signature.first));
    outFile.write(reinterpret_cast<const char*>(&signature.second), sizeof(signature.second));
    outFile.close();
}

std::pair<long long, long long> Signature::readSignatureFromFileElGamal(const std::string& filename) {
    std::ifstream inFile(filename + "-signed.sig", std::ios::binary);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open signature file.");
    }

    long long a, b;
    inFile.read(reinterpret_cast<char*>(&a), sizeof(a));
    inFile.read(reinterpret_cast<char*>(&b), sizeof(b));
    inFile.close();

    return {a, b};
}


std::pair<int, int> Signature::signWithElGamal(const std::string& filename) {
    auto hash = hashFile(filename);
    long long p, g, y, x;
    ElGamalCipher::gen_keys(p, g, y, x);
    auto signature = ElGamalCipher::encrypt(hash, p, g, y); 
    writeSignatureToFileElGamal(filename, signature);
    return {p, x};
}

bool Signature::verifyWithElGamal(const std::string& filename, std::pair<int, int> keys) {
    auto hash = hashFile(filename);
    auto signature = readSignatureFromFileElGamal(filename);
    auto decryptedHash = ElGamalCipher::decrypt(signature.first, signature.second, keys.first, keys.second);
    return hash == decryptedHash;
}


std::pair<long long, long long> Signature::signWithRSA(const std::string& filename) {
    auto hash = hashFile(filename);
    long long e, d, n;
    RSACipher::gen_keys(e, d, n);
    auto signature = RSACipher::encrypt(hash, e, n);
    writeSignatureToFile(filename, signature);
    return {d, n};
}

bool Signature::verifyWithRSA(const std::string& filename, std::pair<long long, long long> keys) {
    long long hash = hashFile(filename);
    long long signature = readSignatureFromFile(filename);
    long long decrypted_hash = RSACipher::decrypt(signature, keys.first, keys.second);
    return hash == decrypted_hash;
}


std::tuple<std::string, unsigned short, unsigned short> Signature::sign_documentGOST(unsigned int p, unsigned short q, unsigned int a, unsigned short x, const std::string& message) {
    unsigned short h = hash_message(message);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, q - 1);
    unsigned short k = dis(gen);

    unsigned short r = mod_exp(a, k, p) % q;
    if (r == 0) {
        return sign_documentGOST(p, q, a, x, message);
    }

    unsigned short s = (k * h + x * r) % q;
    if (s == 0) {
        return sign_documentGOST(p, q, a, x, message);
    }

    return {message, r, s};
}

bool Signature::verify_signatureGOST(unsigned int p, unsigned short q, unsigned int a, unsigned short y, const std::string& message, unsigned short r, unsigned short s) {
    unsigned short h = hash_message(message);

    // if (!(0 < r && r < q) || !(0 < s && s < q)) {
    //     return false;
    // }

    if (!(0 < r && r < q)) {
        return false;
    }


    unsigned short h_inv = mod_inverse(h, q);
    unsigned short u1 = (s * h_inv) % q;
    unsigned short u2 = (-r * h_inv) % q;

    unsigned short v = (mod_exp(a, u1, p) * mod_exp(y, u2, p)) % p % q;

    return v == r;
}
