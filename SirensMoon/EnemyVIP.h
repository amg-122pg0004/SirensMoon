#pragma once
#include "Enemy.h"
#include "ServerMachine.h"

class EnemyVIP : public Enemy {
public:
	EnemyVIP(Game& game, ModeBase& mode, MapChips::EnemyData enemydata,ServerMachine& owner);
	void Init() override;
private:
	ServerMachine& _owner;
};
