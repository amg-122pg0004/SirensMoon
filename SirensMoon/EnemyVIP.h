#pragma once
#include "EnemyA.h"

class ServerMachine;

class EnemyVIP : public EnemyA {
public:
	EnemyVIP(Game& game, ModeGame& mode, ObjectDataStructs::EnemyData enemydata,ServerMachine& owner, ObjectDataStructs::EnemyPatrol patrol, EnemyGenerator::EnemyPattern pattern);
	void Init() override;
	void Update() override;

	void CheckDamage()override;
private:
	ServerMachine& _owner;
};
