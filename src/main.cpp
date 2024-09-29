#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

class lab_1 {
public:
    static int Exponentiation_modulo(long long n, long long e, long long m) {
        long long result = 1;
        long long v = n % m;

        while (e > 0) {
            if (e % 2 == 1) result *= v;
            v = v * v % m;
            e /= 2;
        }

        return result % m;
    }

    static long long Exponentiation_modulo_inverse(long long a, long long p) {
        return Exponentiation_modulo(a, p - 2, p); 
    }

    static void generalized_Euclids_algorithm(int a, int b, std::array<int, 3> &T) {
        #define U table[u ^ it]
        #define V table[v ^ it]

        const int u = 0, v = 1;
        std::array<int, 3> table[2] = {{a, 1, 0}, {b, 0, 1}};
        int it = 0;

        if (b > a) std::swap(U[0], V[0]);

        while(true) {
            if (V[0] == 0) {
                T = table[v];
                if (b > a) std::swap(T[1], T[2]);
                return;
            }

            int q = U[0] / V[0];

            T[0] = U[0] % V[0];
            T[1] = U[1] - q * V[1];
            T[2] = U[2] - q * V[2];

            U = T;

            it ^= 1;
        }
    }

    static void diffie_hellman_key_exchange(long long p, long long g, long long a, long long b) {
        long long Y_a = Exponentiation_modulo(g, a, p);
        long long Y_b = Exponentiation_modulo(g, b, p);
        
        long long Z_a = Exponentiation_modulo(Y_b, a, p);
        long long Z_b = Exponentiation_modulo(Y_a, b, p);
        
        std::cout << "Абонент A получил общий ключ: " << Z_a << std::endl;
        std::cout << "Абонент B получил общий ключ: " << Z_b << std::endl << std::endl;;
    }

    static long long baby_step_giant_step(long long g, long long h, long long p) {
        long long n = static_cast<long long>(std::sqrt(p)) + 1;

        // Шаг младенца: вычисляем g^j для 0 <= j < n и сохраняем в хэш-таблице
        std::unordered_map<long long, long long> baby_steps;
        for (long long j = 0; j < n; ++j) {
            long long value = Exponentiation_modulo(g, j, p);
            baby_steps[value] = j;
        }

        // Вычисляем g^(-n) % p
        long long g_inv_n = Exponentiation_modulo_inverse(Exponentiation_modulo(g, n, p), p);

        // Шаг великана: ищем совпадение
        for (long long i = 0; i < n; ++i) {
            long long giant_step = (h * Exponentiation_modulo(g_inv_n, i, p)) % p;
            if (baby_steps.find(giant_step) != baby_steps.end()) {
                return i * n + baby_steps[giant_step];
            }
        }

        return -1;
    }
};


void task_1() {
    int n = 7, e = 19, m = 100;
    std::cout << "Exp modulo: " << n << " ^ " << e << " % " << m << " = " << lab_1::Exponentiation_modulo(n, e, m) << std::endl << std::endl;
}

void task_2() {
    std::array<int, 3> r;
    int a = 28, b = 19;
    lab_1::generalized_Euclids_algorithm(a, b, r);
    std::cout << "Euclids: " << a << "x + " << b << "y => НОД = " << r[0] << ", x = " << r[1] << ", y = " << r[2] << std::endl << std::endl;;

}

void task_3() {
    long long p = 19, g = 2, X_a = 5, X_b = 7;
    lab_1::diffie_hellman_key_exchange(p, g, X_a, X_b);
}

void task_4() {
    long long g = 2, h = 22, p = 29;

    long long result = lab_1::baby_step_giant_step(g, h, p);
    if (result != -1) {
        std::cout << "Дискретный логарифм: " << result << std::endl;
    } else {
        std::cout << "Логарифм не найден" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    task_1();
    task_2();
    task_3();
    task_4();

    return 0;
}