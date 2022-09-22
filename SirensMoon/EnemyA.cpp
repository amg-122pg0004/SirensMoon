#include "EnemyA.h"
#include "ModeGame.h"
#include "map"
#include <random>

EnemyA::EnemyA(Game& game, ModeGame& mode, EnemyData data, EnemyGenerator::EnemyPattern grdata)
	:Enemy{ game,mode,grdata }, _waitFrame{ data.waitFrame }
{
	_pos = { data.pos.x,data.pos.y };
	_sight_H = data.sightH;
	_sight_W = data.sightW;
	_detectionCompleteFrame = data.detectionComplete;

	_eyePos = _pos;
	_patrolID = data.patrolID;
	_patrolFlag = 1;

	SetPatrolPoints();
};

void EnemyA::Update() {
	Enemy::Update();

	if (_chase) {
		MoveToPlayer();
	}
	if (!_chase && _detectionFrame == 0) {
		if (_patrolLength != 1) {
			if (CheckReachPoint()) {
				++_elapseFrame;
				if (_elapseFrame >= _waitFrame) {
					GetNextPoints();
				}
			}
			else {
				MoveNextPoint();
				_elapseFrame = 0;
			}
		}
	}
}

void EnemyA::SetPatrolPoints() {
	if (_patrolID != -1) {
		auto patroldata = dynamic_cast<ModeGame&>(_mode).GetMapChips()->FindPatrol(_patrolID);
		_patrolPoints = patroldata.PatrolPoints;
		_patrolMode = patroldata.TruckingMode;
		_patrolLength = static_cast<int>(_patrolPoints.size()) - 1;
		int startpoint{ 0 };
		for (int i = 0; i < _patrolPoints.size(); ++i) {
			if ((_patrolPoints[i] - _pos).Length() < (_patrolPoints[startpoint] - _pos).Length()) {
				startpoint = i;
			}
		}
		_patrolIndex = startpoint;
		_nextPos = _patrolPoints[startpoint] - (_size / 2);
	}
	else {
		_patrolPoints.emplace_back(_pos);
		_patrolMode = false;
		_patrolLength = 1;
		_nextPos = _patrolPoints[0];
	}


}

void EnemyA::MoveNextPoint() {
	_dir = _nextPos - _pos;
	_dir.Normalize();
	_pos += _dir * _speed;

}

bool EnemyA::CheckReachPoint() {
	if ((_nextPos - _pos).Length() < 7) {
		return 1;
	}
	else {
		return 0;
	}
}

void EnemyA::GetNextPoints() {
	if (_patrolMode == true) {
		++_patrolIndex;
		if (_patrolIndex > _patrolLength) {
			_patrolIndex = 0;
		}
		_nextPos = _patrolPoints[_patrolIndex];
	}
	else if (_patrolMode == false) {
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

void EnemyA::Debug(Vector2 window_pos, Vector2 camera_pos) {
	Enemy::Debug(window_pos, camera_pos);
}
