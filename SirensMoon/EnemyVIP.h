#pragma once
#include "EnemyA.h"

class ServerMachine;

class EnemyVIP : public EnemyA {
public:
	EnemyVIP(Game& game, ModeGame& mode, ObjectDataStructs::EnemyData enemydata,ServerMachine& owner, ObjectDataStructs::EnemyPatrol patrol, EnemyGenerator::EnemyPattern pattern);
	void Update() override;
	void TakeDamage(Type)override;
	void CheckDamage()override;
private:
	ServerMachine& _owner;
	bool _hitGreenBullet;
};
