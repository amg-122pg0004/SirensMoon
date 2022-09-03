#include "EnemyVIP.h"
#include "ServerMachine.h"
#include "ModeGame.h"

EnemyVIP::EnemyVIP(Game& game, ModeGame& mode, ObjectDataStructs::EnemyData enemydata,
	ServerMachine& owner, ObjectDataStructs::EnemyPatrol patrol, EnemyGenerator::EnemyPattern pattern)
	:EnemyA(game, mode, enemydata,pattern), _owner{ owner }, _hitGreenBullet{false}
{
	Init();
	_patrolPoints = patrol.PatrolPoints;
	_patrolMode = patrol.TruckingMode;
	_patrolLength = static_cast<int>(_patrolPoints.size()) - 1;
	_nextPos = _patrolPoints[0];
}

void EnemyVIP::Update() {
	EnemyA::Update();
	if (_dead == true&&_hitGreenBullet) {
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
				TakeDamage(actor->GetType());
				PlaySoundMem(SoundServer::Find("BulletToEnemy"), DX_PLAYTYPE_BACK);
			}
		}
		if (actor->GetType() == Type::RedBullet) {
			if (Intersect(_collision, actor->GetCollision())) {
				_speed = 15;
				_chase = true;
				PlaySoundMem(SoundServer::Find("BulletToEnemy"), DX_PLAYTYPE_BACK);
			}
		}
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
			if (Intersect(_collision, actor->GetCollision())) {
				dynamic_cast<Player&>(*actor).TakeDamage(GetType());
				TakeDamage(actor->GetType());
			}
		}
	}
}

void EnemyVIP::TakeDamage(Type influence){
	if (influence == Type::GreenBullet) {
		_hitGreenBullet = true;
	}
	else {
		_owner.SetValidFlag(false);
	}
	_dead = true;
}
