#include <mentalPoker/mentalPoker.hpp>


MentalPoker::MentalPoker(int num_players, int num_cards) : num_players(num_players), num_cards(num_cards) {
    deck.resize(num_cards);
    players.reserve(num_players);
    general.resize(5);

    long long p = 101, q = 103;
    long long *e = new long long[num_players];
    long long *d = new long long[num_players];
    long long *n = new long long[num_players];
    RSACipher::gen_keys(e, d, n, p, q, num_players);

    for (int i = 0; i < num_players; ++i)
        players.emplace_back(e[i], d[i], n[i]);

    for (int i = 0; i < num_cards; ++i)
        deck[i] = i + 1;
}

void MentalPoker::shuffle_and_encrypt() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

    for (const auto &player : players) {
        for (auto &card : deck) {
            card = RSACipher::encrypt(card, player.e, player.n);
        }
    }
}

std::vector<std::vector<long long>> MentalPoker::deal_cards(int num_cards) {
    std::vector<std::vector<long long>> hands(num_players);
    for (int i = 0; i < num_players; ++i) {
        for (int j = 0; j < num_cards; ++j) {
            hands[i].push_back(deck.back());
            deck.pop_back();
        }
    }

    for (int i = 0; i < 5; ++i) {
        general[i] = deck.back();
        deck.pop_back();
    }

    return hands;
}

void MentalPoker::reveal_cards(std::vector<long long> &hand, int player_id) {
    for (auto &card : hand) {
        for (int i = 0; i < num_players; ++i) {
            if (i != player_id) {
                card = RSACipher::decrypt(card, players[i].d, players[i].n);
            }
        }
    }

    for (auto &card : hand)
        card = RSACipher::decrypt(card, players[player_id].d, players[player_id].n);
}

void MentalPoker::print_general() const {
    std::cout << "Общие карты: ";
    for (const auto &it : general) {
        long long card = it;
        for (int i = 0; i < num_players; ++i)
            card = RSACipher::decrypt(card, players[i].d, players[i].n);

        std::cout << card << " ";
    }
    std::cout << std::endl;
}