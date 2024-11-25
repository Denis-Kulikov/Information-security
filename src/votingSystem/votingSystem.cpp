#include <votingSystem/votingSystem.hpp>


VotingSystem::VotingSystem() {
    RSACipher::gen_keys(e, d, n);
    std::cout << "Серверные ключи:\n";
    std::cout << "Открытый ключ (e, n): (" << e << ", " << n << ")\n";
    std::cout << "Закрытый ключ d: " << d << "\n";
}

long long VotingSystem::sign_blinded_message(long long blinded_message) {
    return RSACipher::decrypt(blinded_message, d, n);
}

long long VotingSystem::restore_blinded_message(long long signature) {
    return RSACipher::encrypt(signature, e, n);
}
    

bool VotingSystem::verify_vote(long long message, long long signature) {
    return RSACipher::encrypt(signature, e, n) == message;
}

long long VotingSystem::get_public_key_e() { return e; }
long long VotingSystem::get_public_key_n() { return n; }


long long Client::blind_message(long long message, long long e, long long n) {
    r = rand() % (n - 1) + 1;
    while (gcd(r, n) != 1) r = rand() % (n - 1) + 1;
    std::cout << "Слепящий фактор клиента: " << r << "\n";
    return (message * mod_exp(r, e, n)) % n;
}

long long Client::unblind_signature(long long blinded_signature, long long n) {
    long long r_inv = mod_inverse(r, n);
    return (blinded_signature * r_inv) % n;
}