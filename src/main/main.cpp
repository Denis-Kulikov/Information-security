#include <mentalPoker/mentalPoker.hpp>

#define N 4


int main() {
    MentalPoker poker(N, 52);
    poker.shuffle_and_encrypt();
    auto hands = poker.deal_cards(2);

    for (int i = 0; i < N; ++i) {
        std::cout << "Карты игрока " << i + 1 << ": ";
        poker.reveal_cards(hands[i], i);

        for (const auto &card : hands[i])
            std::cout << card << " ";
        std::cout << "\n";
    }
    poker.print_general();

    return 0;
}
