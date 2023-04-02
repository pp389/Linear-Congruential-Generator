#include "MathematicalUtilities.h"

int GCD(int a, int b) {
	int temp;
	while (b != 0) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

bool isPrime(int number) {
	if (number < 2)
		return false;

	for (int i = 2; i * i <= number; i++)
		if (number % i == 0)
			return false;

	return true;
}

std::vector<int> findPrimeDivisors(int number) {
	std::vector<int> divisors;

	for (int i = 2; i <= number; i++)
		if ((number % i == 0) && isPrime(i))
			divisors.push_back(i);

	return divisors;
}