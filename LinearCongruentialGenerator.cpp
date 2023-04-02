#include "LinearCongruentialGenerator.h"
#include "MathematicalUtilities.h"
#include <cmath>
#include <iostream>

void LinearCongruentialGenerator::generateIncrement() {
	increment = 2;

	//we are searching for "increment" value which is relatively prime with given modulus
	while (GCD(increment, modulus) != 1)
		increment++;
}

void LinearCongruentialGenerator::generateMultiplier() {
	std::vector<int> multipliersToCheck;
	int lambda = 1;

	//search for best multiplier and lambda parameter by iterating through possible values of both
	for (int multiplierToCheck = 2; multiplierToCheck < modulus; multiplierToCheck++) {
		//check only values which are relatively prime with modulus
		if (GCD(multiplierToCheck, modulus) == 1) {
			int lambdaToCheck = 1;
			long long multiplToTheLambdaPower = pow(multiplierToCheck, lambdaToCheck);

			//lambda iterating
			while (multiplToTheLambdaPower > 0) {
				if (multiplToTheLambdaPower % modulus == 1) {
					//searching for higher lambda value
					if (lambdaToCheck > lambda) {
						//we found better lamba
						lambda = lambdaToCheck;
						multipliersToCheck.clear();
						multipliersToCheck.push_back(multiplierToCheck);
					}
					else if (lambdaToCheck == lambda)
						multipliersToCheck.push_back(multiplierToCheck);
				}
				lambdaToCheck++;
				multiplToTheLambdaPower = pow(multiplierToCheck, lambdaToCheck);
			}
		}
	}
	int bestMultiplier = 1;
	for (int multiplierGuess : multipliersToCheck) {
		if (checkConditionsForMultiplier(multiplierGuess)) {
			multiplier = multiplierGuess;
			return;
		}
		else
			bestMultiplier = multiplierGuess;
	}

	if (bestMultiplier == 1 && multipliersToCheck.size() > 0)
		multiplier = multipliersToCheck.back();
	else
		multiplier = bestMultiplier;
}

bool LinearCongruentialGenerator::checkConditionsForMultiplier(int multiplier) const {
	//"b" is the value defined in theorem as multiplier minus 1
	int b = multiplier - 1;

	//we need all prime divisors of modulus to check one of the conditions
	std::vector<int> primeDivisiors = findPrimeDivisors(modulus);

	//first condition: check if "b" is multiple for every "p" (which is prime divisor of modulus)
	for (int p : primeDivisiors)
		if (p % b != 0)
			return false;

	//second condition: if modulus % 4 == 0, b % 4 also must be 0
	if ((modulus % 4 == 0) && (b % 4) != 0)
		return false;

	return true;
}

void LinearCongruentialGenerator::generateNumbers() {
	modulus = maxValue + 1;
	generateMultiplier();
	generateIncrement();

	int number = seed;
	for (int i = 0; i < numberOfValues; i++) {
		number = (multiplier * number + increment) % modulus;

		generatedNumbers.push_back(number);
	}
}

void LinearCongruentialGenerator::viewGeneratedNumbers() const {
	for (int number : generatedNumbers)
		std::cout << number << std::endl;
}

void LinearCongruentialGenerator::saveGeneratedNumbersToFile() const {
	for (int i = 0; i < generatedNumbers.size(); i++)
		outputFile << generatedNumbers[i] << std::endl;
}
