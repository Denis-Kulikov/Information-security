#include <algorithm>
#include <vector>
#include <random>
#include "../cipher/cipher.hpp"

struct Player {
    long long e, d, n;

    Player(long long e, long long d, long long n)
        : e(e), d(d), n(n) {}

    Player() {
        RSACipher::gen_keys(e, d, n);
    }
};

class MentalPoker {
private:
    std::vector<long long> deck;
    std::vector<Player> players;
    std::vector<long long> general;
    int num_players;
    int num_cards;

public:
    MentalPoker(int num_players, int num_cards);
    void shuffle_and_encrypt();
    std::vector<std::vector<long long>> deal_cards(int num_cards);
    void reveal_cards(std::vector<long long> &hand, int player_id);
    void print_general() const;
};