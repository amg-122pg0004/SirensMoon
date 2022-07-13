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

Enemy::Enemy(Game& game,ModeBase& mode,Vector2 pos) :Actor{ game,mode }, _speed{5}
{
	_validLight = true;
	_cg=ImageServer::LoadGraph("resource/Enemy/up.png");
	_pos = {pos.x+700,pos.y+900};
	_initPos = pos;
	SetPatrolPoints();

};

void Enemy::Update() {
	if (CheckReachPoint()) {
		GetNextPoints();
	}
	else {
		MoveNextPoint();
	}
}

void Enemy::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg, 0);
}

void Enemy::SetPatrolPoints() {
	Vector2 a = { _initPos.x+700, _initPos.y+900 };
	_patrolPoints.emplace_back(a);
	Vector2 b = { _initPos.x + 100, _initPos.y + 900 };
	_patrolPoints.emplace_back(b);
	Vector2 c = { _initPos.x + 100, _initPos.y + 100 };
	_patrolPoints.emplace_back(c);
	Vector2 d = { _initPos.x + 700,_initPos.y + 100 };
	_patrolPoints.emplace_back(d);

	_patrolLength = _patrolPoints.size()-1;
	_nextPos = _patrolPoints[1];
}

void Enemy::MoveNextPoint() {
	Vector2 dir = _nextPos - _pos;
	dir.Normalize();
	_pos += dir * _speed;
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
	++_patrolIndex;
	if (_patrolIndex > _patrolLength) {
		_patrolIndex = 0;
	}
	_nextPos=_patrolPoints[_patrolIndex];
}
