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

Enemy::Enemy(Game& game,ModeBase& mode,MapChips::EnemyData enemydata) :Actor{ game,mode }, _speed{5}
{
	_validLight = true;
	_cg=ImageServer::LoadGraph("resource/Enemy/up.png");
	_pos = {enemydata.StartPosition.x,enemydata.StartPosition.y};
	_patrolID = enemydata.patrolID;
	_patrolFlag = 1;
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
	_patrolPoints = dynamic_cast<ModeGame&>(_mode).GetMapChips()->FindPatrol(_patrolID).PatrolPoints;
	_patrolLength = _patrolPoints.size()-1;
	_nextPos = _patrolPoints[0];
	_patrolMode = dynamic_cast<ModeGame&>(_mode).GetMapChips()->FindPatrol(_patrolID).TruckingMode;
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
	if (_patrolMode = true) {
		++_patrolIndex;
		if (_patrolIndex > _patrolLength) {
			_patrolIndex = 0;
		}
		_nextPos = _patrolPoints[_patrolIndex];
	}
	else if(_patrolMode =false) {
		_patrolIndex = _patrolFlag + _patrolFlag;
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
		
	}	
}
