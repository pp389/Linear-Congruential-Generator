#include "LibFiles.h"
#include "Exceptions.h"
#include <iostream>

std::string addExtensionIfNotPresent(std::string fileName) {
	return fileName.find(".txt") == std::string::npos ? fileName + ".txt" : fileName;
}

void openFile(std::fstream& file, std::string fileName) {
	addExtensionIfNotPresent(fileName);
	try {
		file.open(fileName.c_str(), std::ios::in | std::ios::out);
		//check if the file which we want to open already exists
		if (!file.is_open()) {
			std::ofstream newFile(fileName);
			file.open(fileName.c_str(), std::ios::in | std::ios::out);
		}

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	if (!file.good())
		throw Exceptions::FileOpenException();
}
