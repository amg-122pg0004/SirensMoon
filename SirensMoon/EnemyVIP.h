#pragma once
#include "Enemy.h"

class ServerMachine;

class EnemyVIP : public Enemy {
public:
	EnemyVIP(Game& game, ModeBase& mode, MapChips::EnemyData enemydata,ServerMachine& owner, MapChips::EnemyPatrol patrol);
	void Init() override;
	void Update() override;
private:
	ServerMachine& _owner;
};
