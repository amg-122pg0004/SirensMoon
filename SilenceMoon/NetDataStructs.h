#pragma once
#include <string>
#include <memory>
#include <vector>
#include <random>
#include "Math.h"

enum class DataType {
	RandomData,
	InputData,
	PositionFix
};

class NetworkDataBase {
public:
	DataType type;
	int length;
};

class  InputData :public NetworkDataBase {
public:
	int frame;
	int key;
	Vector2 analog;
};

class  RandomData :public NetworkDataBase {
public:
	unsigned int random;
};

class  PositionFixData :public NetworkDataBase {
public:
	Vector2 Position;
};