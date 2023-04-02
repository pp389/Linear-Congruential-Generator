#include "LinearCongruentialGenerator.h"
#include "AdditiveCongruentialMethod.h"
#include "LibFiles.h"
#include "Exceptions.h"
#include <iostream>

void checkIfValuesAreValid(int numberOfValues, int maxValue, int seed) {
	if ((numberOfValues < 0) || (maxValue <= 0) || (seed < 0 || seed >= maxValue)) {
		throw Exceptions::InvalidInputValueException();
	}
}

int main() {
	try {
		int numberOfValues, maxValue, seed;
		std::string outputFileName;

		std::cout << "Number of values to generate: ";
		std::cin >> numberOfValues;

		std::cout << "Maximum value which can be generated: ";
		std::cin >> maxValue;

		std::cout << "Seed: ";
		std::cin >> seed;

		std::cout << "Output file name: ";
		std::cin >> outputFileName;

		std::fstream outputFile;
		openFile(outputFile, outputFileName);

		checkIfValuesAreValid(numberOfValues, maxValue, seed);

		std::cout << "Choose generator (1 - Linear congruential generator, 2 - Additive congruential method): ";
		int method;
		std::cin >> method;

		if (method == 1) {
			LinearCongruentialGenerator generator(numberOfValues, maxValue, seed, outputFile);
			generator.generateNumbers();
			generator.saveGeneratedNumbersToFile();
		}
		else if (method == 2) {
			std::string fileWithPairsName;
			std::fstream fileWithPairs;

			std::cout << "Name of file with pairs: ";
			std::cin >> fileWithPairsName;

			openFile(fileWithPairs, fileWithPairsName);

			AdditiveCongruentialMethodGenerator generator(numberOfValues, maxValue, seed, outputFile, fileWithPairs);
			generator.generateNumbers();
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}