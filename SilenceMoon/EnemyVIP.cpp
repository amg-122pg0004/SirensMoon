#include "EnemyVIP.h"
#include "ServerMachine.h"
#include "ModeGame.h"
#include <random>

EnemyVIP::EnemyVIP(Game& game, ModeGame& mode, EnemyData enemydata,
	ServerMachine& owner, EnemyPatrol patrol, EnemyGenerator::EnemyPattern pattern, unsigned int random)
	:EnemyA(game, mode, enemydata,pattern), _owner{ owner }, _hitGreenBullet{false},_random{random}
{
	Init();
	_patrolPoints = patrol.PatrolPoints;
	_patrolMode = patrol.TruckingMode;
	_patrolLength = static_cast<int>(_patrolPoints.size()) - 1;
	_nextPos = _patrolPoints[0];
	_pos = _patrolPoints[_game.GetFrameCount() % _patrolPoints.size()];
}

void EnemyVIP::Update() {
	EnemyA::Update();
	if (_hitGreenBullet) {
		_owner.DeadEnemyVIP();
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
	_speed = 1;
	_chase = false;
	Respawn();
}

void EnemyVIP::Respawn(){
	Vector2 player0pos = { 0,0 };
	Vector2 player1pos = { 0,0 };
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			player0pos = dynamic_cast<Player&>(*actor).GetRoomPosition();
		}
		if (actor->GetType() == Type::PlayerB) {
			player1pos = dynamic_cast<Player&>(*actor).GetRoomPosition();
		}
	}


	ModeGame& mode = dynamic_cast<ModeGame&>(_mode);
	auto vipdata = mode.GetMapChips()->GetPatrolPointsVIP();

	if (vipdata.size() < 4) {
		return;
	}

	std::mt19937 engine(_random);
	std::shuffle(vipdata.begin(), vipdata.end(), engine);

	int i = 0;
	for (i; i < vipdata.size(); ++i) {
		auto pos = vipdata[i].PatrolPoints[0];
		int count_x3 = static_cast<int>(floor(pos.x / (static_cast<double>(screen_W) / 2)));
		int count_y3 = static_cast<int>(floor(pos.y / screen_H));
		if (count_x3 != player0pos.x || count_y3 != player0pos.y) {
			if (count_x3 != player1pos.x || count_y3 != player1pos.y) {
				break;
			}
		}
	}

	auto loot = vipdata[i];
	Vector2 pos = loot.PatrolPoints[0];
	auto id = loot.ID;
	_patrolPoints = vipdata[i].PatrolPoints;
	_patrolMode = vipdata[i].TruckingMode;
	_patrolLength = static_cast<int>(_patrolPoints.size()) - 1;
	_nextPos = _patrolPoints[0];
	_pos = _patrolPoints[_game.GetFrameCount() % _patrolPoints.size()];
}
