#include "EnemyVIP.h"
#include "Math.h"
#include "ImageServer.h"
#include "ModeGame.h"
#include "BlinkLight.h"
#include "SoundServer.h"
#include <random>

EnemyVIP::EnemyVIP(Game& game, ModeBase& mode, MapChips::EnemyData enemydata, ServerMachine& owner) :Enemy(game, mode, enemydata), _owner{ owner }
{
	_generatedEnemy=_owner.GetGeneratedEnemy();
}

void EnemyVIP::Init() {
	Enemy::Init();
}
