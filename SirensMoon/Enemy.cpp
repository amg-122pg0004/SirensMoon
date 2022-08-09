/*****************************************************************//**
 * \file   Enemy.cpp
 * \brief  基本敵キャラクター
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Enemy.h"
#include "Math.h"
#include "ImageServer.h"
#include "ModeGame.h"
#include "BlinkLight.h"
#include "SoundServer.h"
#include <random>

Enemy::Enemy(Game& game,ModeGame& mode,MapChips::EnemyData enemydata, EnemyGenerator::EnemyPattern pattern)
	:Actor{ game,mode }, _speed{ 1 }, _sight_H{ 210 }, _sight_W{330}, _detectionFrame{ 0 },_chase{false}
{
	_size = { 200,200 };
	_pos = {enemydata.StartPosition.x,enemydata.StartPosition.y};
	_patrolID = enemydata.patrolID;
	_patrolFlag = 1;
	_eyePos = _pos;
	SetPatrolPoints();
	auto light = std::make_unique<BlinkLight>(_game, _mode, *this);
	_mode.GetActorServer().Add(std::move(light));

	_generatedEnemy.emplace_back(pattern.head);
	_generatedEnemy.emplace_back(pattern.body);
	_generatedEnemy.emplace_back(pattern.foot);
	Init();
};

void Enemy::Init() {
	/*
	Resize(_cg_top);
	Resize(_cg_top2);
	Resize(_cg_mid);
	Resize(_cg_bot);
	*/

	switch (_generatedEnemy[0]) {
	case 1:
		_cg_top[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_down.png");
		_cg_top[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_downleft.png");
		_cg_top[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_left.png");
		_cg_top[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_upleft.png");
		_cg_top[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_up.png");
		_cg_top[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_upright.png");
		_cg_top[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_right.png");
		_cg_top[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_downright.png");

		_cg_top2[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft]=ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		break;
	case 2:
		_cg_top[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_down.png");
		_cg_top[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downleft.png");
		_cg_top[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_left.png");
		_cg_top[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upleft.png");
		_cg_top[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_up.png");
		_cg_top[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upright.png");
		_cg_top[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_right.png");
		_cg_top[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downright.png");

		_cg_top2[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downleft.png");
		_cg_top2[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_left.png");
		_cg_top2[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upleft.png");
		_cg_top2[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upright.png");
		_cg_top2[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_right.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downright.png");
		break;
	case 3:
		_cg_top[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_down.png");
		_cg_top[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downleft.png");
		_cg_top[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_left.png");
		_cg_top[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upleft.png");
		_cg_top[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_up.png");
		_cg_top[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upright.png");
		_cg_top[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_right.png");
		_cg_top[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downright.png");

		_cg_top2[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downleft.png");
		_cg_top2[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_left.png");
		_cg_top2[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upleft.png");
		_cg_top2[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upright.png");
		_cg_top2[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_right.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downright.png");
		break;
	}
	switch (_generatedEnemy[1]) {
	case 1:
		_cg_mid[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/body1/body1_down.png");
		_cg_mid[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/body1/body1_downleft.png");
		_cg_mid[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/body1/body1_left.png");
		_cg_mid[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/body1/body1_upleft.png");
		_cg_mid[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/body1/body1_up.png");
		_cg_mid[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/body1/body1_upright.png");
		_cg_mid[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/body1/body1_right.png");
		_cg_mid[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/body1/body1_downright.png");
		break;
	case 2:
		_cg_mid[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/body2/body2_down.png");
		_cg_mid[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downleft.png");
		_cg_mid[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/body2/body2_left.png");
		_cg_mid[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upleft.png");
		_cg_mid[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/body2/body2_up.png");
		_cg_mid[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upright.png");
		_cg_mid[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/body2/body2_right.png");
		_cg_mid[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downright.png");
		break;
	case 3:
		_cg_mid[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/body2/body2_down.png");
		_cg_mid[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downleft.png");
		_cg_mid[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/body2/body2_left.png");
		_cg_mid[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upleft.png");
		_cg_mid[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/body2/body2_up.png");
		_cg_mid[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upright.png");
		_cg_mid[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/body2/body2_right.png");
		_cg_mid[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downright.png");
		break;
	}
	switch (_generatedEnemy[2]) {
	case 1:
		_cg_bot[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_down.png");
		_cg_bot[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_downleft.png");
		_cg_bot[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_left.png");
		_cg_bot[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_upleft.png");
		_cg_bot[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_up.png");
		_cg_bot[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_upright.png");
		_cg_bot[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_right.png");
		_cg_bot[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_downright.png");
		break;
	case 2:
		_cg_bot[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_down.png");
		_cg_bot[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downleft.png");
		_cg_bot[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_left.png");
		_cg_bot[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upleft.png");
		_cg_bot[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_up.png");
		_cg_bot[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upright.png");
		_cg_bot[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_right.png");
		_cg_bot[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downright.png");
		break;
	case 3:
		_cg_bot[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_down.png");
		_cg_bot[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downleft.png");
		_cg_bot[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_left.png");
		_cg_bot[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upleft.png");
		_cg_bot[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_up.png");
		_cg_bot[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upright.png");
		_cg_bot[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_right.png");
		_cg_bot[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downright.png");
		break;
	}


	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::PlayerA) {
			_lastDetection = actor.get();
		}
	}
}

void Enemy::Resize(std::map<EnemyDirection, std::vector<int>> set) {
	
	set[EnemyDirection::Down].resize(1);
	set[EnemyDirection::DownLeft].resize(1);
	set[EnemyDirection::Left].resize(1);
	set[EnemyDirection::UpLeft].resize(1);
	set[EnemyDirection::Up].resize(1);
	set[EnemyDirection::UpRight].resize(1);
	set[EnemyDirection::Right].resize(1);
	set[EnemyDirection::DownRight].resize(1);

}

void Enemy::Update() {
	if (_chase) {
		MoveToPlayer();
	}
	else {
		if (_patrolLength != 1) {
			if (CheckReachPoint()) {
				GetNextPoints();
			}
			else {
				MoveNextPoint();
			}
		}
	}


	SightUpdate();
	if (CheckDetection()) {
		++_detectionFrame;
		if (_detectionFrame >= 120) {
			_speed = 15;
			_chase = true;
		}
	}
	else {
		_detectionFrame = 0;
	}
	AnimationUpdate();
	UpdateCollision();
	CheckDamage();
}

void Enemy::AnimationUpdate() {
	_animeNo = _game.GetFrameCount()/2 % 29;
	SetDirection();
}

void Enemy::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x + window_pos.x - camera_pos.x+_size.x ),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y+_size.y),
		_cg_bot[_cg_direction],
		1);
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x ),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y ),
		static_cast<int>(_pos.x + window_pos.x - camera_pos.x + _size.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y + _size.y ),
		_cg_top2[_cg_direction], 
		1);
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x + window_pos.x - camera_pos.x + _size.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y + _size.y),
		_cg_mid[_cg_direction],
		1);
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y ),
		static_cast<int>(_pos.x + window_pos.x - camera_pos.x + _size.x ),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y + _size.y ),
		_cg_top[_cg_direction],
		1);
}

void Enemy::SetPatrolPoints() {
	if (_patrolID != -1) {
		auto patroldata = dynamic_cast<ModeGame&>(_mode).GetMapChips()->FindPatrol(_patrolID);
		_patrolPoints = patroldata.PatrolPoints;
		_patrolMode = patroldata.TruckingMode;
		_patrolLength = static_cast<int>(_patrolPoints.size()) - 1;
		int startpoint{0};
		for (int i = 0; i < _patrolPoints.size();++i) {
			if ((_patrolPoints[i]-_pos).Length() < (_patrolPoints[startpoint]-_pos).Length()) {
				startpoint = i;
			}
		}
		_patrolIndex=startpoint;
		_nextPos = _patrolPoints[startpoint]-(_size / 2);
	}
	else {
		_patrolPoints.emplace_back(_pos);
		_patrolMode = false;
		_patrolLength = 1;
		_nextPos = _patrolPoints[0];
	}
	

}

void Enemy::MoveNextPoint() {
	_dir = _nextPos - _pos;
	_dir.Normalize();
	_pos += _dir * _speed;

}

bool Enemy::CheckReachPoint() {
	if ((_nextPos - _pos).Length() < 7) {
		return 1;
	}
	else {
		return 0;
	}
}

void Enemy::GetNextPoints() {
	if (_patrolMode == true) {
		++_patrolIndex;
		if (_patrolIndex > _patrolLength) {
			_patrolIndex = 0;
		}
		_nextPos = _patrolPoints[_patrolIndex];
	}
	else if(_patrolMode == false) {
		_patrolIndex = _patrolIndex + _patrolFlag;
		if (_patrolIndex > _patrolLength) 
		{
			_patrolIndex -= 2;
			_patrolFlag = -1;
		}
		if (_patrolIndex < 0) 
		{
			_patrolIndex += 2;
			_patrolFlag = 1;
		}
		_nextPos = _patrolPoints[_patrolIndex];
	}	
}

void Enemy::SightUpdate() {
	_eyePos = _pos + _size / 2;
	auto fov = _eyePos + _dir * _sight_W;
	Vector2 dirside = { _dir.y * -1,_dir.x };//<視界に垂直なベクトル
	/*視界範囲4点作成*/
	_sightPos.pos1 = { _eyePos.x - dirside.x*(_sight_H/2),_eyePos.y-dirside.y*(_sight_H/2)};
	_sightPos.pos2 = { _eyePos.x + dirside.x * (_sight_H/2),_eyePos.y + dirside.y * (_sight_H/2) };
	_sightPos.pos3 = { (_eyePos + _dir * _sight_W).x - dirside.x * (_sight_H/2),(_eyePos + _dir * _sight_W).y - dirside.y * (_sight_H/2)};
	_sightPos.pos4 = { (_eyePos + _dir * _sight_W).x + dirside.x * (_sight_H/2),(_eyePos + _dir * _sight_W).y + dirside.y * (_sight_H/2) };
}

bool Enemy::CheckDetection() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
			CheckRoomPosition();
			if (_roomPosition.x == actor->GetRoomPosition().x && _roomPosition.y == actor->GetRoomPosition().y) {
				auto col = actor->GetCollision();
				Vector2 righttop = { col.max.x,col.min.y };
				Vector2 leftbottom = { col.min.x,col.max.y };

				AABB enemyaround = { {0,0},{0,0} };
				enemyaround.min = { _eyePos.x - 60,_eyePos.y - 75 };
				enemyaround.max = { _eyePos.x + 60,_eyePos.y + 75 };
				/*周辺判定*/
				if (Intersect(enemyaround, col)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*pos1,pos2は周辺判定の範囲に含まれるため判定を行わない*/
				/*pos2,pos4とプレイヤーコリジョン4辺*/
				if (IsCrossed(_sightPos.pos2, _sightPos.pos4, col.min, righttop) ||
					IsCrossed(_sightPos.pos2, _sightPos.pos4, righttop, col.max) ||
					IsCrossed(_sightPos.pos2, _sightPos.pos4, col.max, leftbottom) ||
					IsCrossed(_sightPos.pos2, _sightPos.pos4, leftbottom, col.min)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*pos1,pos3とプレイヤーコリジョン4辺*/
				if (IsCrossed(_sightPos.pos1, _sightPos.pos3, col.min, righttop) ||
					IsCrossed(_sightPos.pos1, _sightPos.pos3, righttop, col.max) ||
					IsCrossed(_sightPos.pos1, _sightPos.pos3, col.max, leftbottom) ||
					IsCrossed(_sightPos.pos1, _sightPos.pos3, leftbottom, col.min)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*pos3,pos4とプレイヤーコリジョン4辺*/
				if (IsCrossed(_sightPos.pos3, _sightPos.pos4, col.min, righttop) ||
					IsCrossed(_sightPos.pos3, _sightPos.pos4, righttop, col.max) ||
					IsCrossed(_sightPos.pos3, _sightPos.pos4, col.max, leftbottom) ||
					IsCrossed(_sightPos.pos3, _sightPos.pos4, leftbottom, col.min)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*視界内に完全に納まっている場合の確認*/
				if (Vector2::Cross(_sightPos.pos1 - _sightPos.pos3, col.min - _sightPos.pos3) < 0 &&
					Vector2::Cross(_sightPos.pos3 - _sightPos.pos4, col.min - _sightPos.pos4) < 0 &&
					Vector2::Cross(_sightPos.pos4 - _sightPos.pos2, col.min - _sightPos.pos2) < 0 &&
					Vector2::Cross(_sightPos.pos2 - _sightPos.pos1, col.min - _sightPos.pos1) < 0) {
					_lastDetection = actor.get();
					return 1;
				}
			}
		}
	}
	return 0;
}

bool Enemy::IsCrossed(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
	Vector2 vec_a1 = b - a;
	Vector2 vec_a2 = c - a;
	Vector2 vec_a3 = d - a;

	Vector2 vec_c1 = a - c;
	Vector2 vec_c2 = b - c;
	Vector2 vec_c3 = d - c;

	if (Vector2::Cross(vec_a1, vec_a2) * Vector2::Cross(vec_a1, vec_a3) < 0) {
		if (Vector2::Cross(vec_c3, vec_c1) * Vector2::Cross(vec_c3, vec_c2) < 0) {
			return 1;
		}
	}
	return 0;
}

void Enemy::SetDirection() {
	double dir_rad = atan2(_dir.y,_dir.x);
	double pi = 3.141519;
	double dir_deg = (dir_rad) * 180 / 3.14;

	if (-180 < dir_deg && dir_deg <= -140) {
		_cg_direction = EnemyDirection::Left;
	}
	else if (-140 < dir_deg && dir_deg <= -100) {
		_cg_direction = EnemyDirection::UpLeft;
	}
	else if (-100 < dir_deg && dir_deg <= -60) {
		_cg_direction = EnemyDirection::Up;
	}
	else if (-60 < dir_deg && dir_deg <=-20 ) {
		_cg_direction = EnemyDirection::UpRight;
	}
	else if (-20 < dir_deg && dir_deg <=20) {
		_cg_direction = EnemyDirection::Right;
	}
	else if (20 < dir_deg && dir_deg <=60) {
		_cg_direction = EnemyDirection::DownRight;
	}
	else if (60 < dir_deg && dir_deg <=100) {
		_cg_direction = EnemyDirection::Down;
	}
	else if(100 < dir_deg && dir_deg <= 140) {
		_cg_direction = EnemyDirection::DownLeft;
	}
	else if (140 < dir_deg && dir_deg <= 180) {
		_cg_direction = EnemyDirection::Left;
	}
}

void Enemy::CheckDamage() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::RedBullet) {
			if(Intersect(_collision, actor->GetCollision())) {
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

void Enemy::MoveToPlayer() {
	auto col = dynamic_cast<Player&>(*_lastDetection).GetCollision();
	_dir = (col.min + col.max) / 2 - (_collision.min + _collision.max) / 2;
	_dir.Normalize();
	_pos += _dir * _speed;

}

void Enemy::ApplyDamage() {
	dynamic_cast<Player&>(*_lastDetection).TakeDamage();
	_dead = true;
}

void Enemy::UpdateCollision() {
	_collision.min = { _pos.x+70,_pos.y+30 };
	_collision.max = { _pos.x+_size.x - 70,_pos.y+_size.y - 30 };
}

void Enemy::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(stageNum,window_pos,camera_pos);
	/*周辺知覚範囲表示*/
	DrawBox(static_cast<int>(_eyePos.x + window_pos.x - camera_pos.x -60),
		static_cast<int>(_eyePos.y + window_pos.y - camera_pos.y -75),
		static_cast<int>(_eyePos.x + window_pos.x - camera_pos.x +60),
		static_cast<int>(_eyePos.y + window_pos.y - camera_pos.y + 75),
		GetColor(255, 0, 0), 0);

	/*視野範囲表示*/
	DrawLine(static_cast<int>(_sightPos.pos1.x + window_pos.x - camera_pos.x),
			static_cast<int>(_sightPos.pos1.y + window_pos.y - camera_pos.y),
			static_cast<int>(_sightPos.pos2.x + window_pos.x - camera_pos.x),
			static_cast<int>(_sightPos.pos2.y + window_pos.y - camera_pos.y),
			GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_sightPos.pos2.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos2.y + window_pos.y - camera_pos.y),
		static_cast<int>(_sightPos.pos4.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos4.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_sightPos.pos4.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos4.y + window_pos.y - camera_pos.y),
		static_cast<int>(_sightPos.pos3.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos3.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_sightPos.pos3.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos3.y + window_pos.y - camera_pos.y),
		static_cast<int>(_sightPos.pos1.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos1.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);

	//発見フレーム数表示
	std::stringstream ss;
	ss << "発見フレーム数" << _detectionFrame << "\n";
	DrawString(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y - 10),
		ss.str().c_str(), GetColor(255, 0, 255));
}