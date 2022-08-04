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
	:Actor{ game,mode }, _speed{ 1 }, _sight_H{ 210 }, _sight_W{330}, _detectionFrame{ 0 }
{
	_size = { 60,90 };
	_cg_top.resize(30);
	_cg_mid.resize(30);
	_cg_bot.resize(30);

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
	switch (_generatedEnemy[0]) {
	case 1:
		ImageServer::LoadDivGraph("resource/Enemy/red_top2.png", 30, 5, 6, 250, 370, _cg_top.data());
		break;
	case 2:
		ImageServer::LoadDivGraph("resource/Enemy/blue_top2.png", 30, 5, 6, 250, 370, _cg_top.data());
		break;
	case 3:
		ImageServer::LoadDivGraph("resource/Enemy/green_top2.png", 30, 5, 6, 250, 370, _cg_top.data());
		break;
	}
	switch (_generatedEnemy[1]) {
	case 1:
		ImageServer::LoadDivGraph("resource/Enemy/red_mid2.png", 30, 5, 6, 250, 370, _cg_mid.data());
		break;
	case 2:
		ImageServer::LoadDivGraph("resource/Enemy/blue_mid2.png", 30, 5, 6, 250, 370, _cg_mid.data());
		break;
	case 3:
		ImageServer::LoadDivGraph("resource/Enemy/green_mid2.png", 30, 5, 6, 250, 370, _cg_mid.data());
		break;
	}
	switch (_generatedEnemy[2]) {
	case 1:
		ImageServer::LoadDivGraph("resource/Enemy/red_bot2.png", 30, 5, 6, 250, 370, _cg_bot.data());
		break;
	case 2:
		ImageServer::LoadDivGraph("resource/Enemy/blue_bot2.png", 30, 5, 6, 250, 370, _cg_bot.data());
		break;
	case 3:
		ImageServer::LoadDivGraph("resource/Enemy/green_bot2.png", 30, 5, 6, 250, 370, _cg_bot.data());
		break;
	}
}

void Enemy::Update() {
	if (_patrolLength != 1) {
		if (CheckReachPoint()) {
			GetNextPoints();
		}
		else {
			MoveNextPoint();
		}
	}

	SightUpdate();
	if (CheckDetection()) {
		++_detectionFrame;
		if (_detectionFrame >= 120) {
			ApplyDamage();
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
}

void Enemy::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x + window_pos.x - camera_pos.x+_size.x ),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y+_size.y),
		_cg_top[_animeNo],
		1);
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x ),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y ),
		static_cast<int>(_pos.x + window_pos.x - camera_pos.x + _size.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y + _size.y ),
		_cg_mid[_animeNo],
		1);
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y ),
		static_cast<int>(_pos.x + window_pos.x - camera_pos.x + _size.x ),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y + _size.y ),
		_cg_bot[_animeNo],
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
	if ((_nextPos - _pos).Length() < 5) {
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
		if (actor->GetType() == Type::PlayerA|| actor->GetType() == Type::PlayerB) {
			auto col=actor->GetCollision();
			Vector2 righttop = { col.max.x,col.min.y };
			Vector2 leftbottom = { col.min.x,col.max.y };

			AABB enemyaround={{0,0},{0,0}};
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
			if (Vector2::Cross(_sightPos.pos1 - _sightPos.pos3, col.min - _sightPos.pos3)<0 &&
				Vector2::Cross(_sightPos.pos3 - _sightPos.pos4, col.min - _sightPos.pos4)<0 &&
				Vector2::Cross(_sightPos.pos4 - _sightPos.pos2, col.min - _sightPos.pos2)<0 &&
				Vector2::Cross(_sightPos.pos2 - _sightPos.pos1, col.min - _sightPos.pos1)<0) {
				_lastDetection = actor.get();
				return 1;
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

void Enemy::CheckDamage() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::Bullet) {
			if(Intersect(_collision, actor->GetCollision())) {
				actor->Dead();
				_dead = true;
				PlaySoundMem(SoundServer::Find("BulletToEnemy"), DX_PLAYTYPE_BACK);
			}
		}
	}
}

void Enemy::ApplyDamage() {
	dynamic_cast<Player&>(*_lastDetection).TakeDamage();
	_dead = true;
}

void Enemy::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
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