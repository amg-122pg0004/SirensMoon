#include "EnemyB.h"
#include "ModeGame.h"


EnemyB::EnemyB(Game& game, ModeGame& mode, ObjectDataStructs::EnemyBData data, EnemyGenerator::EnemyPattern pattern)
	:Enemy{game,mode,pattern},_data{data},_index{0},_elapsed{0}
{
	_pos = { data.StartPosition.x,data.StartPosition.y };
}

void EnemyB::Update(){
	auto radian=_data.Direction[_index]*3.141519 / 180;
	_dir.x = sin(radian);
	_dir.y = cos(radian);

	++_elapsed;
	if (_elapsed > _data.LookTime[_index]) {
		++_index;
		_elapsed = 0;
		while (_data.LookTime[_index] == 0) {
			++_index;
			if (_index >= _data.Direction.size()) {
				_index = 0;
			}
		}
	}
	if (_index >= _data.Direction.size()) {
		_index = 0;
	}

	Enemy::Update();
}

void EnemyB::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	Enemy::Debug(stageNum, window_pos, camera_pos);
}