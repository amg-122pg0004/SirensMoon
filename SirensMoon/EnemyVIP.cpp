#include "EnemyVIP.h"
#include "ServerMachine.h"

EnemyVIP::EnemyVIP(Game& game, ModeBase& mode, MapChips::EnemyData enemydata, ServerMachine& owner) :Enemy(game, mode, enemydata), _owner{ owner }
{
	_generatedEnemy=_owner.GetGeneratedEnemy();
	Init();
}

void EnemyVIP::Init() {
	Enemy::Init();
}

void EnemyVIP::Update() {
	Enemy::Update();
	if (!_owner.GetValidFlag()) {
		_dead = true;
	}
}
