#include "EnemyB.h"
#include "ModeGame.h"


EnemyB::EnemyB(Game& game, ModeGame& mode, EnemyBData data, EnemyGenerator::EnemyPattern pattern)
	:Enemy{game,mode,pattern},_data{data},_index{0},_elapsed{0}
{
	_pos = { data.pos.x,data.pos.y };
	_sight_H = data.sightH;
	_sight_W = data.sightW;
	_detectionCompleteFrame = data.detectionComplete;
}

void EnemyB::Update(){
	if (_chase) {
		MoveToPlayer();
	}
	else {
		auto radian = Math::ToRadians(_data.Direction[_index]);
		_dir.x = sin(radian);
		_dir.y = cos(radian);

		++_elapsed;
		if (_elapsed > _data.LookTime[_index]) {
			++_index;
			_elapsed = 0;
			for (int i = _index; i < 4; ++i) {
				if (_data.LookTime[_index] == 0) {
					++_index;
					if (_index >= _data.Direction.size()) {
						_index = 0;
					}
				}
				else {
					break;
				}
			}
		}
		if (_index >= _data.Direction.size()) {
			_index = 0;
		}
	}
	Enemy::Update();
}

void EnemyB::Debug(Vector2 window_pos, Vector2 camera_pos) {
	Enemy::Debug(window_pos, camera_pos);
}