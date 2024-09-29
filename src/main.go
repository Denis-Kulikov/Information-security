package main

import (
	"fmt"
	"math"
)

type Lab1 struct{}

func (Lab1) ExponentiationModulo(n, e, m int64) int64 {
	result := int64(1)
	v := n % m

	for e > 0 {
		if e%2 == 1 {
			result = (result * v) % m
		}
		v = (v * v) % m
		e /= 2
	}

	return result % m
}

func (l Lab1) ExponentiationModuloInverse(a, p int64) int64 {
	return l.ExponentiationModulo(a, p-2, p)
}

func (Lab1) GeneralizedEuclidsAlgorithm(a, b int, T *[3]int) {
	u, v := 0, 1
	table := [2][3]int{{a, 1, 0}, {b, 0, 1}}
	it := 0

	getU := func() [3]int {
		return table[u^it]
	}

	getV := func() [3]int {
		return table[v^it]
	}

	if b > a {
		table[u], table[v] = table[v], table[u]
	}

	for {
		if getV()[0] == 0 {
			*T = getU()
			if b > a {
				T[1], T[2] = T[2], T[1]
			}
			return
		}

		q := getU()[0] / getV()[0]

		T[0] = getU()[0] % getV()[0]
		T[1] = getU()[1] - q*getV()[1]
		T[2] = getU()[2] - q*getV()[2]

		table[u^it] = *T
		it ^= 1
	}
}

func (l Lab1) DiffieHellmanKeyExchange(p, g, a, b int64) {
	Y_a := l.ExponentiationModulo(g, a, p)
	Y_b := l.ExponentiationModulo(g, b, p)

	Z_a := l.ExponentiationModulo(Y_b, a, p)
	Z_b := l.ExponentiationModulo(Y_a, b, p)

	fmt.Printf("Абонент A получил общий ключ: %d\n", Z_a)
	fmt.Printf("Абонент B получил общий ключ: %d\n\n", Z_b)
}

func (l Lab1) BabyStepGiantStep(g, h, p int64) int64 {
	n := int64(math.Sqrt(float64(p))) + 1

	babySteps := make(map[int64]int64)
	for j := int64(0); j < n; j++ {
		value := l.ExponentiationModulo(g, j, p)
		babySteps[value] = j
	}

	gInvN := l.ExponentiationModuloInverse(l.ExponentiationModulo(g, n, p), p)

	for i := int64(0); i < n; i++ {
		giantStep := (h * l.ExponentiationModulo(gInvN, i, p)) % p
		if j, ok := babySteps[giantStep]; ok {
			return i*n + j
		}
	}

	return -1
}

func task1() {
	l := Lab1{}
	n, e, m := int64(7), int64(19), int64(100)
	fmt.Printf("Exp modulo: %d ^ %d %% %d = %d\n\n", n, e, m, l.ExponentiationModulo(n, e, m))
}

func task2() {
	var r [3]int
	a, b := 28, 19
	Lab1{}.GeneralizedEuclidsAlgorithm(a, b, &r)
	fmt.Printf("Euclids: %dx + %dy => НОД = %d, x = %d, y = %d\n\n", a, b, r[0], r[1], r[2])
}

func task3() {
	p, g, X_a, X_b := int64(19), int64(2), int64(5), int64(7)
	Lab1{}.DiffieHellmanKeyExchange(p, g, X_a, X_b)
}

func task4() {
	g, h, p := int64(2), int64(22), int64(29)
	result := Lab1{}.BabyStepGiantStep(g, h, p)
	if result != -1 {
		fmt.Printf("Дискретный логарифм: %d\n", result)
	} else {
		fmt.Println("Логарифм не найден")
	}
}

func main() {
	task1()
	task2()
	task3()
	task4()
}
