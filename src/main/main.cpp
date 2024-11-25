#include <votingSystem/votingSystem.hpp>


int main() {
    srand(time(nullptr));
    VotingSystem server;
    Client client;

    std::cout << "\nВыберите вариант голосования (1: Да, 2: Нет, 3: Воздержался): ";
    int choice;
    std::cin >> choice;

    long long message;
    if (choice == 1) message = 1;
    else if (choice == 2) message = 2;
    else message = 3;

    long long blinded_message = client.blind_message(message, server.get_public_key_e(), server.get_public_key_n());
    std::cout << "Заслеплённое сообщение (m'): " << blinded_message << "\n";

    long long blinded_signature = server.sign_blinded_message(blinded_message);
    std::cout << "Подпись заслеплённого сообщения (s'): " << blinded_signature << "\n";

    long long signature = client.unblind_signature(blinded_signature, server.get_public_key_n());
    std::cout << "Чистая подпись (s): " << signature << "\n";

    long long vote = server.restore_blinded_message(signature);
    std::cout << "\nГолос отправлен: (" << message << ", " << vote << ")\n";

    return 0;
}
