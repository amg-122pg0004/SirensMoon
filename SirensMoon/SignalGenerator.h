#pragma once
#include <vector>

class SignalGenerator {
public:
	SignalGenerator();
	std::vector<int> GetPattern() { return _pattern; }

	static const std::vector<bool> GetSignal(int index) {
		static const std::vector<std::vector<bool>> signal = {
			{1,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,},
			{1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,0,0,},
			{1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,0},
			{1,0,1,0,1,0,1,0,1,0,0,0,}
		};
		return signal[index];
	}

private:

	std::vector<int> _pattern;
};