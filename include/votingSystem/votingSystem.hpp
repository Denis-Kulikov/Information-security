#include "../cipher/cipher.hpp"

class VotingSystem {
    long long e, d, n;

public:
    VotingSystem();

    long long sign_blinded_message(long long blinded_message);
    long long restore_blinded_message(long long signature);
    bool verify_vote(long long message, long long signature);

    long long get_public_key_e();
    long long get_public_key_n();
};

class Client {
    long long r;

public:
    long long blind_message(long long message, long long e, long long n);
    long long unblind_signature(long long blinded_signature, long long n);
};