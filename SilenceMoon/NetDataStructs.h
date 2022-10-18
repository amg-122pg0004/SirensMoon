#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Math.h"

enum class DataType {
	EnemyGenerate,
	PlayerPosition,
	TakeDamage,
	KillEnemy,
	RespawnEnemy,
	ShootBullet,
	ActivateGimmick
};

class NetworkDataBase {
public:
	DataType type;
	int length;
};

struct  EnemyGenerateData :public NetworkDataBase {
public:
	int data[255];
};

struct  PlayerPosition :public NetworkDataBase {
public:
	double data[2];
};

struct  ShootBullet :public NetworkDataBase {
public:
	double position[2];
	double vector[2];
};

struct  KillEnemy :public NetworkDataBase {
public:
	double position[2];
	double vector[2];
};