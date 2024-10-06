package main

import (
	"fmt"
	"math"
)

type Lab1 struct{}

func (Lab1) ExponentiationModulo(n, e, m int) int {
	result := int(1)
	v := n % m

	for e > 0 {
		if e%2 == 1 {
			result = (result * v) % m
		}
		v = (v * v) % m
		e >>= 1
	}

	return result % m
}

func (l Lab1) ExponentiationModuloInverse(a, p int) int {
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

func (l Lab1) DiffieHellmanKeyExchange(p, g, a, b int) {
	Y_a := l.ExponentiationModulo(g, a, p)
	Y_b := l.ExponentiationModulo(g, b, p)

	Z_a := l.ExponentiationModulo(Y_b, a, p)
	Z_b := l.ExponentiationModulo(Y_a, b, p)

	fmt.Printf("Абонент A получил общий ключ: %d\n", Z_a)
	fmt.Printf("Абонент B получил общий ключ: %d\n\n", Z_b)
}

func (l Lab1) BabyStepGiantStep(a, y, p int) int {
	n := int(math.Sqrt(float64(p))) + 1

	babySteps := make(map[int]int)
	for j := int(0); j < n; j++ {
		value := l.ExponentiationModulo(a, j, p)
		babySteps[value] = j
	}

	gInvN := l.ExponentiationModuloInverse(l.ExponentiationModulo(a, n, p), p)

	for i := int(0); i < n; i++ {
		giantStep := (y * l.ExponentiationModulo(gInvN, i, p)) % p
		if j, ok := babySteps[giantStep]; ok {
			return i*n + j
		}
	}

	return -1
}

func task1() {
	n, e, m := int(7), int(19), int(100)
	fmt.Printf("Exp modulo: %d ^ %d %% %d = %d\n\n", n, e, m, Lab1{}.ExponentiationModulo(n, e, m))
}

func task2() {
	var r [3]int
	a, b := 28, 19
	Lab1{}.GeneralizedEuclidsAlgorithm(a, b, &r)
	fmt.Printf("Euclids: %dx + %dy => НОД = %d, x = %d, y = %d\n\n", a, b, r[0], r[1], r[2])
}

func task3() {
	p, g, X_a, X_b := int(11), int(2), int(5), int(7)

	var r [3]int
	Lab1{}.GeneralizedEuclidsAlgorithm(p, g, &r)
	if r[0] != 1 {
		fmt.Printf("p = %d и g = %d - не взаимно простые числа\n\n", p, g)
		return
	}

	Lab1{}.DiffieHellmanKeyExchange(p, g, X_a, X_b)
}

func task4() {
	a, y, p := int(2), int(22), int(29)
	result := Lab1{}.BabyStepGiantStep(a, y, p)
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
