#include "SignalGenerator.h"
#include <algorithm>
#include <random>
#include <numeric>

SignalGenerator::SignalGenerator(){
	std::vector<int> pattern = { 1,2,3,4 };

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(pattern.begin(), pattern.end(), engine);
}