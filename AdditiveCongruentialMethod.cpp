#include "AdditiveCongruentialMethod.h"
#include "LinearCongruentialGenerator.h"
#include "LibFiles.h"
#include <iostream>

std::vector<int> reverse(std::vector<int> vectorToBeReversed) {
	std::vector<int> reversed;

	for (int i = vectorToBeReversed.size() - 1; i >= 0; i--)
		reversed.push_back(vectorToBeReversed[i]);

	return reversed;
}

std::pair<int, int> AdditiveCongruentialMethodGenerator::choosePair() {
	int firstValue, secondValue;
	std::pair<int, int> result;
	while (!fileWithPairs.eof()) {
		fileWithPairs >> firstValue;
		fileWithPairs >> secondValue;

		int maxDifference = 0;
		if (secondValue < LinearCongruentialGenerator::getNumberOfValues()) {
			if ((secondValue - firstValue) > maxDifference) {
				maxDifference = secondValue - firstValue;
				result.first = firstValue;
				result.second = secondValue;
			}
		}
	}
	fileWithPairs.close();
	return result;
}

void AdditiveCongruentialMethodGenerator::generateNumbers() {
	std::vector<int> xValues;
	int numberOfValues = LinearCongruentialGenerator::getNumberOfValues();
	xValues.reserve(numberOfValues);

	LinearCongruentialGenerator::generateNumbers();
	xValues = LinearCongruentialGenerator::getGeneratedNumbers();

	std::vector<int> yValues = reverse(xValues);

	int modulus = LinearCongruentialGenerator::getMaxValue() + 1;

	std::pair<int, int> pair = choosePair();

	for (int i = 0; i < numberOfValues; i++) {
		outputFile << yValues[pair.first] << std::endl;

		numbers.push_back(yValues[pair.first]);

		pair.first--;
		pair.second--;

		if (pair.first <= 0)
			pair.first = numberOfValues - 1;
		if (pair.second <= 0)
			pair.second = numberOfValues - 1;
	}
}
