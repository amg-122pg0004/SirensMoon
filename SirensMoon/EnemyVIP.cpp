#include "EnemyVIP.h"
#include "ServerMachine.h"
#include "ModeGame.h"
#include "SoundServer.h"

EnemyVIP::EnemyVIP(Game& game, ModeGame& mode, MapChips::EnemyData enemydata,
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
	if (_dead == true) {
		_owner.DeadEnemyVIP();
	}
	if (!_owner.GetValidFlag()) {
		_dead = true;
	}
}

void EnemyVIP::CheckDamage(){
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::GreenBullet) {
			if (Intersect(_collision, actor->GetCollision())) {
				actor->Dead();
				_dead = true;
				PlaySoundMem(SoundServer::Find("BulletToEnemy"), DX_PLAYTYPE_BACK);
			}
		}
		if (actor->GetType() == Type::GreenBullet) {
			if (Intersect(_collision, actor->GetCollision())) {
				_speed = 15;
				_chase = true;
				PlaySoundMem(SoundServer::Find("BulletToEnemy"), DX_PLAYTYPE_BACK);
			}
		}
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
			if (Intersect(_collision, actor->GetCollision())) {
				dynamic_cast<Player&>(*actor).TakeDamage();
				_dead = true;
			}
		}
	}
}
