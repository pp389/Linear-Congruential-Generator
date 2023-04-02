#pragma once
#include <fstream>
#include <vector>
#include "LinearCongruentialGenerator.h"

class AdditiveCongruentialMethodGenerator : public LinearCongruentialGenerator {
private:
	std::fstream& fileWithPairs;
	std::fstream& outputFile;

	//constains generated numbers
	std::vector<int> numbers;

	/**
	* Chooses a pair of numbers from file handled by "fileWithPairs" std::fstream object.
	*/
	std::pair<int, int> choosePair();

public:
	AdditiveCongruentialMethodGenerator(int nOfValues, int maxVal, int seed, std::fstream& output, std::fstream& fWithPairs) :
		LinearCongruentialGenerator(nOfValues, maxVal, seed, output), fileWithPairs(fWithPairs), outputFile(output) { }

	~AdditiveCongruentialMethodGenerator() { fileWithPairs.close(); outputFile.close(); };
	
	/**
	* Starts additive congruential method generator and saves results of its work to specified file and std::vector container "generatedNumbers".
	*/
	virtual void generateNumbers();
};
