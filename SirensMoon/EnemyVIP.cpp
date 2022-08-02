#include "EnemyVIP.h"
#include "ServerMachine.h"

EnemyVIP::EnemyVIP(Game& game, ModeBase& mode, MapChips::EnemyData enemydata, 
	ServerMachine& owner, MapChips::EnemyPatrol patrol, EnemyGenerator::EnemyPattern pattern)
	:Enemy(game, mode, enemydata,pattern), _owner{ owner }
{
	_generatedEnemy=_owner.GetGeneratedEnemy();
	Init();
	_patrolPoints = patrol.PatrolPoints;
	_patrolMode = patrol.TruckingMode;
	_patrolLength = static_cast<int>(_patrolPoints.size()) - 1;
	_nextPos = _patrolPoints[0];
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
