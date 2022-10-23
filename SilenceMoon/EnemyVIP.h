#pragma once
#include "EnemyA.h"

class ServerMachine;

class EnemyVIP : public EnemyA {
public:
	EnemyVIP(Game& game, ModeGame& mode, EnemyData enemydata,ServerMachine& owner, EnemyPatrol patrol, EnemyGenerator::EnemyPattern pattern, unsigned int random);
	void Update() override;
	void TakeDamage(Type)override;
	void CheckDamage()override;
	void Respawn();
private:
	ServerMachine& _owner;
	bool _hitGreenBullet;
	unsigned int _random;
};
