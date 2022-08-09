#pragma once
#include "Enemy.h"
#include "EnemyGenerator.h"

class ServerMachine;

class EnemyVIP : public Enemy {
public:
	EnemyVIP(Game& game, ModeGame& mode, MapChips::EnemyData enemydata,ServerMachine& owner, MapChips::EnemyPatrol patrol,EnemyGenerator::EnemyPattern pattern);
	void Init() override;
	void Update() override;

	void CheckDamage()override;
private:
	ServerMachine& _owner;
};
