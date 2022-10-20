#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Math.h"

enum class DataType {
	InputData,
	EnemyGenerate,
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

class  EnemyGenerateData :public NetworkDataBase {
public:
	int data[255];
};