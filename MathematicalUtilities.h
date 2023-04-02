#pragma once
#include <vector>

/**
* Calculates greatest common divisor of two numbers
* @param a - first value
* @param a - second value
* @return integer value which is greatest common divisor of specified values
*/
int GCD(int a, int b);

/**
* Checks if given number is prime
* @param number - number to check
* @return true if number is prime or false otherwise
*/
bool isPrime(int number);

/**
* Finds all prime divisors of given number
* @param number - number to check
* @return std::vector which contains all found prime divisiors of given number
*/
std::vector<int> findPrimeDivisors(int number);